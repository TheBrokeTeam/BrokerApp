//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#include "BAJson.h"
#include "../Utils/BAString.h"

const rapidjson::Value BAJson::kEmptyArray = rapidjson::Value(rapidjson::kArrayType);
const rapidjson::Value BAJson::kEmptyObject = rapidjson::Value(rapidjson::kObjectType);

rapidjson::Document BAJson::document()
{
    auto document = rapidjson::Document();
    document.SetObject();

    return document;
}

rapidjson::Value BAJson::array()
{
    return rapidjson::Value(rapidjson::kArrayType);
}

rapidjson::Value BAJson::object()
{
    return rapidjson::Value(rapidjson::kObjectType);
}

bool BAJson::getBool(const rapidjson::Value& object, const char* key, bool defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsBool()) {
        return defaultValue;
    }

    return object[key].GetBool();
}

int BAJson::getInt(const rapidjson::Value& object, const char* key, int defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsInt()) {
        return defaultValue;
    }

    return object[key].GetInt();
}

float BAJson::getFloat(const rapidjson::Value& object, const char* key, float defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsNumber()) {
        return defaultValue;
    }

    return object[key].GetFloat();
}

int64_t BAJson::getLong(const rapidjson::Value& object, const char* key, int64_t defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsInt64()) {
        return defaultValue;
    }

    return object[key].GetInt64();
}

double BAJson::getDouble(const rapidjson::Value& object, const char* key, double defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsNumber()) {
        return defaultValue;
    }

    return object[key].GetDouble();
}

std::string BAJson::getString(const rapidjson::Value& object, const char* key, const std::string& defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsString()) {
        return defaultValue;
    }

    return object[key].GetString();
}

const char* BAJson::getStringConst(const rapidjson::Value& object, const char* key, const char* defaultValue)
{
    if (!object.HasMember(key) || !object[key].IsString()) {
        return defaultValue;
    }

    return object[key].GetString();
}

//cocos2d::Size BAJson::getSize(const rapidjson::Value& object, const char* key, const cocos2d::Size& defaultValue)
//{
//    if (!object.HasMember(key) || !object[key].IsString()) {
//        return defaultValue;
//    }
//
//    float width, height;
//    sscanf(object[key].GetString(), "%f;%f", &width, &height);
//
//    return cocos2d::Size(width, height);
//}

std::vector<std::string> BAJson::getStringVector(const rapidjson::Value& object, const char* key)
{
    return getVector<std::string, const char*, &rapidjson::Value::IsString, &rapidjson::Value::GetString>(object, key);
}

std::vector<int> BAJson::getIntVector(const rapidjson::Value& object, const char* key)
{
    return getVector<int, int, &rapidjson::Value::IsInt, &rapidjson::Value::GetInt>(object, key);
}

std::vector<float> BAJson::getFloatVector(const rapidjson::Value& object, const char* key)
{
    return getVector<float, float, &rapidjson::Value::IsNumber, &rapidjson::Value::GetFloat>(object, key);
}

bool BAJson::parse(const std::string& json, rapidjson::Document& document)
{
    document.Parse(json.c_str(), json.length());

    if (document.HasParseError()) {
        return false;
    }

    return true;
}

bool BAJson::parseFile(const std::string& filePath, rapidjson::Document& document)
{
//    auto contents = FileUtils::getInstance()->getStringFromFile(filePath);
//
//    if (contents.size() == 0)
//    {
//        OPDebug::warn("Json", "Could not parse JSON file. It is empty or was not found: " + filePath);
//        return 0;
//    }
//    return parse(contents, document)

    FILE* fp = fopen(filePath.c_str(), "r"); // non-Windows use "r"

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    document.ParseStream(is);

    fclose(fp);

    return !document.IsNull();
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, bool boolValue)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    object.AddMember(name, boolValue, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, int intValue)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    object.AddMember(name, intValue, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, float floatValue)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    object.AddMember(name, floatValue, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, int64_t int64Value)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    object.AddMember(name, (int64_t)int64Value, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, double doubleValue)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    object.AddMember(name, doubleValue, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, const std::string& stringValue)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    rapidjson::Value value(stringValue.c_str(), (unsigned int)stringValue.size(), document.GetAllocator());

    object.AddMember(name, value, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, const char* stringValue)
{
    set(document, object, key, stringValue, strlen(stringValue));
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, const char* stringValue, std::size_t size)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    rapidjson::Value value(stringValue, (unsigned int)size, document.GetAllocator());

    object.AddMember(name, value, document.GetAllocator());
}

void BAJson::set(rapidjson::Document& document, rapidjson::Value& object, const std::string& key, rapidjson::Value& value)
{
    rapidjson::Value name(key.c_str(), (unsigned int)key.size(), document.GetAllocator());
    object.AddMember(name, value, document.GetAllocator());
}

void BAJson::set(rapidjson::Document &document, const std::string &key, rapidjson::Value &value)
{
    set(document, document, key, value);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, bool boolValue)
{
    set(document, document, key, boolValue);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, int intValue)
{
    set(document, document, key, intValue);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, float floatValue)
{
    set(document, document, key, floatValue);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, int64_t int64Value)
{
    set(document, document, key, int64Value);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, double doubleValue)
{
    set(document, document, key, doubleValue);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, const std::string& stringValue)
{
    set(document, document, key, stringValue);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, const char* stringValue)
{
    set(document, document, key, stringValue);
}

void BAJson::set(rapidjson::Document& document, const std::string& key, const char* stringValue, std::size_t size)
{
    set(document, document, key, stringValue, size);
}

std::string BAJson::toString(const rapidjson::Value& value, bool pretty)
{
    rapidjson::StringBuffer buffer;

    if (pretty)
    {
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        value.Accept(writer);
    }
    else
    {
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        value.Accept(writer);
    }

    return std::string(buffer.GetString(), buffer.GetSize());
}


void BAJson::append(rapidjson::Document& document, bool boolValue)
{
    append(document, document, boolValue);
}

void BAJson::append(rapidjson::Document& document, int intValue)
{
    append(document, document, intValue);
}

void BAJson::append(rapidjson::Document& document, float floatValue)
{
    append(document, document, floatValue);
}

void BAJson::append(rapidjson::Document& document, int64_t int64Value)
{
    append(document, document, int64Value);
}

void BAJson::append(rapidjson::Document& document, double doubleValue)
{
    append(document, document, doubleValue);
}

void BAJson::append(rapidjson::Document& document, const std::string& stringValue)
{
    append(document, document, stringValue);
}

void BAJson::append(rapidjson::Document& document, const char* stringValue)
{
    append(document, document, stringValue);
}

void BAJson::append(rapidjson::Document& document, const char* stringValue, std::size_t size)
{
    append(document, document, stringValue, size);
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& value)
{
    append(document, document, value);
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, bool boolValue)
{
    object.PushBack(boolValue, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, int intValue)
{
    object.PushBack(intValue, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, float floatValue)
{
    object.PushBack(floatValue, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, int64_t int64Value)
{
    object.PushBack((int64_t)int64Value, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, double doubleValue)
{
    object.PushBack(doubleValue, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, const std::string& stringValue)
{
    rapidjson::Value value(stringValue.c_str(), (unsigned int)stringValue.size(), document.GetAllocator());
    object.PushBack(value, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, const char* stringValue)
{
    rapidjson::Value value(stringValue, (unsigned int)strlen(stringValue), document.GetAllocator());
    object.PushBack(value, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, const char* stringValue, std::size_t size)
{
    rapidjson::Value value(stringValue, (unsigned int)size, document.GetAllocator());
    object.PushBack(value, document.GetAllocator());
}

void BAJson::append(rapidjson::Document& document, rapidjson::Value& object, rapidjson::Value& value)
{
    object.PushBack(value, document.GetAllocator());
}

bool BAJson::exists(const rapidjson::Value& value, const std::string& memberName)
{
    return value.IsObject() && value.HasMember(memberName.c_str());
}

bool BAJson::existsPath(rapidjson::Value &value, const std::string &path)
{
    rapidjson::Value* temp = &value;

    auto components = BAString::split(path, '/');

    for (auto comp : components)
    {
        if (comp.size() != 0)
        {
            if (temp->IsObject() && temp->HasMember(comp.c_str())) {
                temp = &(*temp)[comp.c_str()];
            }
            else if (temp->IsArray() && BAString::isNumber(comp))
            {
                int index = BAString::getInt(comp);

                if (index < 0 || index >= temp->Size()) {
                    return false;
                }

                temp = &(*temp)[index];
            }
            else {
                return false;
            }
        }
    }

    return true;
}

void BAJson::save(const rapidjson::Document& document, const std::string& file)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto jsonStr = buffer.GetString();
//    FileUtils::getInstance()->writeStringToFile(jsonStr, file);
}

bool BAJson::hasBool(const rapidjson::Value& object, const std::string& memberName)
{
    if (!exists(object, memberName)) { return false; }
    const auto& member = object[memberName.c_str()];
    return member.IsBool();
}

bool BAJson::hasNumber(const rapidjson::Value& object, const std::string& memberName)
{
    if (!exists(object, memberName)) { return false; }
    const auto& member = object[memberName.c_str()];
    return member.IsNumber();
}

bool BAJson::hasString(const rapidjson::Value& object, const std::string& memberName)
{
    if (!exists(object, memberName)) { return false; }
    const auto& member = object[memberName.c_str()];
    return member.IsString();
}

bool BAJson::hasObject(const rapidjson::Value& object, const std::string& memberName)
{
    if (!exists(object, memberName)) { return false; }
    const auto& member = object[memberName.c_str()];
    return member.IsObject() || member.IsNull();
}

bool BAJson::hasArray(const rapidjson::Value& object, const std::string& memberName)
{
    if (!exists(object, memberName)) { return false; }
    const auto& member = object[memberName.c_str()];
    return member.IsArray() || member.IsNull();
}

std::string BAJson::stringfy(const rapidjson::Document &document) {
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);
    return strbuf.GetString();
}

