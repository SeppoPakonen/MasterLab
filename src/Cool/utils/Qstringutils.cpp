#include "../Cool.h"
#include "Qstringutils.h"

static bool HasName(const QStringList& names, const String& value)
{
	for(const String& s : names)
		if(s == value)
			return true;
	return false;
}

QString QStringUtils::getUniqueName(const QStringList& names, const QString& name)
{
	int i = 0;
	String new_name = name;
	while(HasName(names, new_name)) {
		new_name = Format("%s-%d", name.Begin(), i);
		i++;
	}
	return new_name;
}

QString QStringUtils::getUniqueFileName(const QStringList& names, const QString& name)
{
	int i = 0;
	String base_name = GetFileTitle(name);
	String extension = ToLower(GetFileExt(name));
	String new_name = name;
	while(HasName(names, new_name)) {
		new_name = Format("%s-%04d%s", base_name.Begin(), ++i, extension.Begin());
	}
	return new_name;
}

QString QStringUtils::appendToFilename(const QString& filename, const QString& appendix)
{
	String base_name = GetFileTitle(filename);
	String extension = GetFileExt(filename);
	if(IsNull(extension))
		return base_name + appendix;
	return base_name + appendix + extension;
}

QString QStringUtils::getCleanFileName(QString filename)
{
	for(int i = 0; i < filename.GetCount(); ++i) {
		byte c = (byte)filename[i];
		if(IsAlNum(c) || c == '_' || c == '-' || c == '.' || c == ' ')
			continue;
		filename.Set(i, '-');
	}
	return filename;
}
