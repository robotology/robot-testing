// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <algorithm>
#include <Asserter.h> // used to format the string message
#include <SuitRunner.h>
#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <iostream>
#include <tinyxml.h>

using namespace std;
using namespace RTF;

SuitRunner::SuitRunner(bool verbose)
    : PluginRunner(verbose),
      verbose(verbose) {
}

SuitRunner::~SuitRunner() {
    reset();
}

void SuitRunner::reset() {
    // first clear the test list of the TestRunner
    PluginRunner::reset();

    // delete all the suits which was created
    for(int i=0; i<suits.size(); i++)
        delete suits[i];
    suits.clear();
}

bool SuitRunner::loadSuit(std::string filename) {
    if(verbose)
        cout<<"Loading "<<filename<<endl;

    ErrorLogger& logger  = ErrorLogger::Instance();

    // loading xml file
    TiXmlDocument doc(filename.c_str());
    if(!doc.LoadFile()) {
        string error = Asserter::format("Syntax error while loading %s at line %d. (%s)",
                                        filename.c_str(), doc.ErrorRow(), doc.ErrorDesc());
        logger.addError(error);        
        return false;
    }

    //retrieving root element
    TiXmlElement *root = doc.RootElement();
    if(!root) {
        string error = Asserter::format("Syntax error while loading %s. (No root element)",
                                        filename.c_str());
        logger.addError(error);
        return false;
    }

    if(!compare(root->Value(), "suit")) {
        if(verbose)
            cout<<filename<<" is not a test suit file!"<<endl;
        return false;
    }

    std::string name = (root->Attribute("name")) ? root->Attribute("name") : "unknown";
    TestSuit* suit = new TestSuit(name);

    // retrieving test cases
    for(TiXmlElement* test = root->FirstChildElement(); test;
        test = test->NextSiblingElement()) {
        if(compare(test->Value(), "test")) {

            // load the plugin and add it to the suit

            // keep track of the created plugins
            //plugins.push_back(plugin);

            // set the test case param
            //plugin->test.getContent().setParam(param);

        }
    }

    // add the test suit to the TestRunner
    addTest(suit);

    // keep tracks of the created suits
    suits.push_back(suit);
    return true;
}

bool SuitRunner::loadMultipleSuits(std::string path,
                                         bool recursive) {    
    /*
    if(!recursive)
        return loadPluginsFromPath(path);

    // load from subfolders
    if((path.rfind(PATH_SEPERATOR)==string::npos) ||
        (path.rfind(PATH_SEPERATOR)!=path.size()-1))
        path = path + string(PATH_SEPERATOR);

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path.c_str())) == NULL) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    loadPluginsFromPath(path);

    while((entry = readdir(dir))) {
        if((entry->d_type == DT_DIR) &&
                (string(entry->d_name) != string(".")) &&
                (string(entry->d_name) != string("..")))
        {
            string name = path + string(entry->d_name);
            loadMultiplePlugins(name, recursive);
        }
    }
    closedir(dir);
    */
    return true;
}

bool SuitRunner::loadSuitsFromPath(std::string path) {
    if(verbose)
        cout<<"Loading plug-ins from "<<path<<endl;
/*
    if((path.rfind(PATH_SEPERATOR)==string::npos) ||
        (path.rfind(PATH_SEPERATOR)!=path.size()-1))
        path = path + string(PATH_SEPERATOR);

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path.c_str())) == NULL) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    while((entry = readdir(dir))) {
        string name = entry->d_name;
        if(name.size() > 3) {
            // check for windows .dll
            string ext = name.substr(name.size()-3,3);
            if(ext == "dll")
                loadPlugin(path+name);
        }
        if(name.size() > 2) {
            // check for unix .so
            string ext = name.substr(name.size()-2,2);
            if(ext == "so")
                loadPlugin(path+name);
        }
        if(name.size() > 5) {
            // check for mac .dylib
            string ext = name.substr(name.size()-5,5);
            if(ext == "dylib")
                loadPlugin(path+name);
        }
    }
    closedir(dir);
    */
    return true;
}

inline bool SuitRunner::compare(const char* first, const char* second)
{
    if(!first && !second) return true;
    if(!first || !second) return false;

    string strFirst(first);
    string strSecond(second);
    transform(strFirst.begin(), strFirst.end(), strFirst.begin(),
              (int(*)(int))toupper);
    transform(strSecond.begin(), strSecond.end(), strSecond.begin(),
              (int(*)(int))toupper);

    return (strFirst == strSecond);
}

