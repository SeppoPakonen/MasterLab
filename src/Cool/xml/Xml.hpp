#ifndef _Cool_xml_Xml_hpp_
#define _Cool_xml_Xml_hpp_

namespace Xml {

using QString = String;
using QDomDocument = XmlNode;
using QDomElement = XmlNode;
using QDomNode = XmlNode;

template <class T>
using QVector = Vector<T>;

template <class K, class V>
using QMap = VectorMap<K, V>;

bool docContentFromFile(QDomDocument& doc, const QString& file_name, bool namespace_processing);
bool docContentToFile(const QDomDocument& doc, const QString& file_name);
QString getSubTagContent(const QDomElement& element, const QString& tag_name);
std::pair<QString, QString> getSubTagContentAndContext(const QDomElement& element, const QString& tag_name);
QVector<QDomNode> getDirectChildrenByTagName(const QDomElement& element, const QString& tag_name);
QString getTagContentByAttribute(const QDomElement& element, const QString& tag_name, const QString& attribute, const QString& value,
                                 const QString& default_return = String(), bool direct_children = true);
QString getXmlProperty(const QDomElement& element, const QString& property_name, const QString& default_return = String());
QString getXmlParameter(const QDomElement& element, const QString& property_name, const QString& default_return = String());
bool hasXmlProperty(const QDomElement& element, const QString& property_name);
bool hasXmlParameter(const QDomElement& element, const QString& property_name);
void addXmlProperties(QDomElement& producer, const QMap<QString, QString>& properties);
void setXmlProperty(QDomElement& element, const QString& property_name, const QString& value);
void setXmlParameter(QDomElement& element, const QString& property_name, const QString& value);
void removeXmlProperty(QDomElement& effect, const QString& name);
void removeMetaProperties(QDomElement& producer);
void renameXmlProperty(QDomElement& effect, const QString& old_name, const QString& new_name);
QMap<QString, QString> getXmlPropertyByWildcard(const QDomElement& element, const QString& property_name);

}

#endif
