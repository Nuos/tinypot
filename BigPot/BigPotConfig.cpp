#include "BigPotConfig.h"

BigPotConfig BigPotConfig::_config;

BigPotConfig::BigPotConfig()
{
	_this = &_config;
	//init();
}


BigPotConfig::~BigPotConfig()
{
	//delete doc;
	//write();
}

void BigPotConfig::init(const string& filepath)
{
#ifdef USINGJSON
	_filename = _filepath + "/config.json";
	printf("try find config file: %s\n", _filename.c_str());
	
	Json::Reader reader;
	_content = readStringFromFile(_filename);
	reader.parse(_content, _value);

	if (_value["record"].isObject())
		_record = _value["record"];
#else
	_filename = filepath + "/config.xml";
	printf("try find config file: %s\n", _filename.c_str());
	_doc.LoadFile(_filename.c_str());
#ifdef _DEBUG
	//_doc.Print();
#endif
	//��ʼ���ṹ
	if (_doc.Error())
	{
		//_doc.DeleteChildren();
		_doc.LinkEndChild(_doc.NewDeclaration());
		_root = _doc.NewElement("root");
	}
	else
	{
		_root = _doc.FirstChildElement("root");
	}

	_record = _root->FirstChildElement("record");
	if (!_record)
		_record = _root->InsertFirstChild(_doc.NewElement("record"))->ToElement();
#endif
}

void BigPotConfig::write()
{
#ifdef USINGJSON
	Json::StyledWriter writer;

	_value["record"] = _record;
	_content = writer.write(_value);

	ofstream ofs;
	ofs.open(_filename);
	ofs << _content;
#else
	//_doc.LinkEndChild(_doc.NewDeclaration());
	_doc.LinkEndChild(_root);
	_doc.SaveFile(_filename.c_str());
#endif
}

XMLElement* BigPotConfig::getElement(XMLElement *parent, const char * name)
{
	auto p = parent->FirstChildElement(name);
	if (p)
	{
		return p;
	}
	else
	{
		p = parent->InsertFirstChild(_doc.NewElement(name))->ToElement();
		p->SetText("");
		return p;
	}
}

int BigPotConfig::getRecord(const char * name)
{
	if (strlen(name) == 0) return 0;
	auto mainname = getFilenameWithoutPath(name);
	const char * str = getElement(_record, ("_" + _sha3(mainname)).c_str())->GetText();
	if (!str)
		return 0;
	return atoi(str);
}

void BigPotConfig::removeRecord(const char * name)
{
	if (strlen(name) == 0) return;
	auto mainname = getFilenameWithoutPath(name);
	_record->DeleteChild(getElement(_record, ("_" + _sha3(mainname)).c_str()));
}

void BigPotConfig::setRecord(int v, const char * name)
{
	if (strlen(name) == 0) return;
	auto mainname = getFilenameWithoutPath(name);
	getElement(_record, ("_" + _sha3(mainname)).c_str())
		->SetText(formatString("%d", v).c_str());
}

void BigPotConfig::clearRecord()
{
	if (_record)
	{
		_record->DeleteChildren();
	}
}

std::string BigPotConfig::getString(const char * name, string def /*= ""*/)
{
	auto p = _root->FirstChildElement(name);
	if (p && p->FirstChild())
	{
		return p->GetText();
	}
	else
	{
		return def;
	}
}

int BigPotConfig::getInteger(const char * name, int def /*= 0*/)
{
	return atoi(getString(name, formatString("%d", def)).c_str());
}

double BigPotConfig::getDouble(const char * name, double def /*= 0.0*/)
{
	return atof(getString(name, formatString("%f", def)).c_str());
}

bool BigPotConfig::getBool(bool &v, const char * name)
{
	return atoi(getString(name, "0").c_str()) != 0;
}

void BigPotConfig::setString(const string v, const char * name)
{
	getElement(_root, name)->SetText(v.c_str());
}

void BigPotConfig::setInteger(int v, const char * name)
{
	setString(formatString("%d", v), name);
}

void BigPotConfig::setDouble(double v, const char * name)
{
	setString(formatString("%f", v), name);
}

void BigPotConfig::setBool(bool v, const char * name)
{
	setString(formatString("%d", v != 0), name);
}

