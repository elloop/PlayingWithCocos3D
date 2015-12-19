#include "data_models/TestDataCenter.h"
#include "util/cocos_util.h"
#include "rapid_json/document.h"
#include "cocos2d.h"
#include <cassert>
USING_NS_CC;
using rapidjson::Document;
using rapidjson::Value;

void TestDataCenter::init(const std::string &cfg)
{
    Data data = FileUtils::getInstance()->getDataFromFile(cfg);
    if (!data.isNull()) 
    {
        Document d;
        std::string s((const char*)data.getBytes(), data.getSize());
        d.Parse<rapidjson::kParseDefaultFlags>(s.c_str());
        if (d.HasParseError()) 
        {
            CocosUtil::log("parse test cfg fail\n");
            return;
        }
        CCAssert(d["items"].IsArray(), "items should be array");
        rapidjson::Value &root = d["items"];
        for (rapidjson::SizeType i=0; i<root.Size(); ++i) 
        {
            testSet_.push_back(new TestDataItem(root[i]["icon"].GetString(), 
                root[i]["description"].GetString(), root[i]["page"].GetString()));
        }
    }
}

TestDataCenter::TestDataCenter()
{

}

TestDataCenter::~TestDataCenter()
{
    for (auto & item : testSet_) 
    {
        if (item) 
        {
            delete item;
            item = nullptr;
        }
    }
    testSet_.clear();
    TestSet().swap(testSet_);
}

TestDataItem* TestDataCenter::getTestDataItemByIndex(TestSet::size_type index) const
{
    //if (index > -1 && index < testSet_.size())

    if (index < testSet_.size())
    {
        return testSet_[index];
    }
    return nullptr;
}
