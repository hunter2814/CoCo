/* 
 * File:   PyAttr.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 27, 2013, 5:11 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyAttr.h"
#include "PyType.h"
#include "PyStr.h"
#include <sstream>
using namespace std;

PyAttr::PyAttr(PyObject* self, string method) {
    this->self = self;
    this->method = method;
}

PyAttr::~PyAttr() {
    try {
        delete self;
    } catch (...) {}
}

PyType* PyAttr::getType() {
    return PyTypes[PyBuiltInType];
}

bool PyAttr::allowableArgCount(int count) {
    PyType* type = self->getType();
    
    int argcount = type->getArgCount(method);
    
    return (argcount == 0) || (argcount-1 == count);
}

string PyAttr::callName() {
    return method;
}

PyObject* PyAttr::__call__(vector<PyObject*>* args) {
    PyType* type = self->getType();
    
    return type->call(method,self,args);
}

PyObject* PyAttr::__type__(vector<PyObject*>* args) {
    return PyTypes[PyBuiltInType];
}

string PyAttr::toString() {
    ostringstream s;
    s << "<built-in method " << method << " of " << self->getType()->toString() << " object at " << this << ">";
    return s.str();
}

PyObject* PyAttr::__str__(vector<PyObject*>* args) {
    return new PyStr(toString());
}