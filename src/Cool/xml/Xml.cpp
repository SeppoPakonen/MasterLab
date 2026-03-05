#include "../Cool.h"
#include "Xml.hpp"

namespace Xml {

static void CollectByTagName(const QDomElement& node, const QString& tag_name, bool direct_children, QVector<QDomNode>& out)
{
	for(int i = 0; i < node.GetCount(); ++i) {
		const QDomNode& child = node[i];
		if(!child.IsTag())
			continue;
		if(child.GetTag() == tag_name) {
			QDomNode copy(child, 1);
			out.AddPick(pick(copy));
		}
		if(!direct_children)
			CollectByTagName(child, tag_name, false, out);
	}
}

static int FindNamedProperty(const QDomElement& element, const QString& tag_name, const QString& property_name)
{
	for(int i = 0; i < element.GetCount(); ++i) {
		const QDomNode& child = element[i];
		if(!child.IsTag(tag_name))
			continue;
		if(child.Attr("name") == property_name)
			return i;
	}
	return -1;
}

bool docContentFromFile(QDomDocument& doc, const QString& file_name, bool)
{
	String xml_text = LoadFile(file_name);
	if(IsNull(xml_text))
		return false;
	doc = ParseXML(xml_text);
	return !doc.IsEmpty();
}

bool docContentToFile(const QDomDocument& doc, const QString& file_name)
{
	return SaveFile(file_name, AsXML(doc, XML_HEADER | XML_DOCTYPE | XML_PRETTY));
}

QString getSubTagContent(const QDomElement& element, const QString& tag_name)
{
	QVector<QDomNode> nodes = getDirectChildrenByTagName(element, tag_name);
	return nodes.IsEmpty() ? String() : nodes[0].GatherText();
}

std::pair<QString, QString> getSubTagContentAndContext(const QDomElement& element, const QString& tag_name)
{
	QVector<QDomNode> nodes = getDirectChildrenByTagName(element, tag_name);
	if(nodes.IsEmpty())
		return {};
	return {nodes[0].GatherText(), nodes[0].Attr("context")};
}

QVector<QDomNode> getDirectChildrenByTagName(const QDomElement& element, const QString& tag_name)
{
	QVector<QDomNode> out;
	CollectByTagName(element, tag_name, true, out);
	return out;
}

QString getTagContentByAttribute(const QDomElement& element, const QString& tag_name, const QString& attribute, const QString& value,
                                 const QString& default_return, bool direct_children)
{
	QVector<QDomNode> nodes;
	CollectByTagName(element, tag_name, direct_children, nodes);
	for(const QDomNode& n : nodes)
		if(n.Attr(attribute) == value)
			return n.GatherText();
	return default_return;
}

QString getXmlProperty(const QDomElement& element, const QString& property_name, const QString& default_return)
{
	return getTagContentByAttribute(element, "property", "name", property_name, default_return, false);
}

QString getXmlParameter(const QDomElement& element, const QString& property_name, const QString& default_return)
{
	return getTagContentByAttribute(element, "parameter", "name", property_name, default_return, false);
}

bool hasXmlProperty(const QDomElement& element, const QString& property_name)
{
	return FindNamedProperty(element, "property", property_name) >= 0;
}

bool hasXmlParameter(const QDomElement& element, const QString& property_name)
{
	return FindNamedProperty(element, "parameter", property_name) >= 0;
}

void addXmlProperties(QDomElement& producer, const QMap<QString, QString>& properties)
{
	for(int i = 0; i < properties.GetCount(); ++i) {
		QDomNode& prop = producer.Add("property");
		prop.SetAttr("name", properties.GetKey(i));
		prop.AddText(properties[i]);
	}
}

void setXmlProperty(QDomElement& element, const QString& property_name, const QString& value)
{
	int pos = FindNamedProperty(element, "property", property_name);
	if(pos >= 0) {
		QDomNode& prop = element.At(pos);
		prop.Remove(0);
		prop.AddText(value);
		return;
	}
	QDomNode& prop = element.Add("property");
	prop.SetAttr("name", property_name);
	prop.AddText(value);
}

void setXmlParameter(QDomElement& element, const QString& property_name, const QString& value)
{
	int pos = FindNamedProperty(element, "parameter", property_name);
	if(pos < 0)
		return;
	element.At(pos).SetAttr("value", value);
}

void removeXmlProperty(QDomElement& effect, const QString& name)
{
	int pos = FindNamedProperty(effect, "property", name);
	if(pos >= 0)
		effect.Remove(pos);
}

void renameXmlProperty(QDomElement& effect, const QString& old_name, const QString& new_name)
{
	int pos = FindNamedProperty(effect, "property", old_name);
	if(pos >= 0)
		effect.At(pos).SetAttr("name", new_name);
}

QMap<QString, QString> getXmlPropertyByWildcard(const QDomElement& element, const QString& property_name)
{
	QMap<QString, QString> out;
	QVector<QDomNode> props = getDirectChildrenByTagName(element, "property");
	for(const QDomNode& prop : props) {
		String key = prop.Attr("name");
		if(key.StartsWith(property_name))
			out.GetAdd(key) = prop.GatherText();
	}
	return out;
}

void removeMetaProperties(QDomElement& producer)
{
	for(int i = producer.GetCount() - 1; i >= 0; --i) {
		const QDomNode& n = producer[i];
		if(n.IsTag("property") && n.Attr("name").StartsWith("meta"))
			producer.Remove(i);
	}
}

}
