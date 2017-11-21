//
// Generated file, do not edit! Created by nedtool 5.1 from inet/linklayer/ethernet/EtherFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "EtherFrame_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(EtherTraffic)

EtherTraffic::EtherTraffic(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

EtherTraffic::EtherTraffic(const EtherTraffic& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EtherTraffic::~EtherTraffic()
{
}

EtherTraffic& EtherTraffic::operator=(const EtherTraffic& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EtherTraffic::copy(const EtherTraffic& other)
{
}

void EtherTraffic::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void EtherTraffic::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class EtherTrafficDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherTrafficDescriptor();
    virtual ~EtherTrafficDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherTrafficDescriptor)

EtherTrafficDescriptor::EtherTrafficDescriptor() : omnetpp::cClassDescriptor("inet::EtherTraffic", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

EtherTrafficDescriptor::~EtherTrafficDescriptor()
{
    delete[] propertynames;
}

bool EtherTrafficDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherTraffic *>(obj)!=nullptr;
}

const char **EtherTrafficDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherTrafficDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherTrafficDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int EtherTrafficDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *EtherTrafficDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int EtherTrafficDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherTrafficDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **EtherTrafficDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherTrafficDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherTrafficDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherTraffic *pp = (EtherTraffic *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherTrafficDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherTraffic *pp = (EtherTraffic *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherTrafficDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherTraffic *pp = (EtherTraffic *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool EtherTrafficDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherTraffic *pp = (EtherTraffic *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *EtherTrafficDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *EtherTrafficDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherTraffic *pp = (EtherTraffic *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EtherJam)

EtherJam::EtherJam(const char *name, short kind) : ::inet::EtherTraffic(name,kind)
{
    this->abortedPkTreeID = 0;
}

EtherJam::EtherJam(const EtherJam& other) : ::inet::EtherTraffic(other)
{
    copy(other);
}

EtherJam::~EtherJam()
{
}

EtherJam& EtherJam::operator=(const EtherJam& other)
{
    if (this==&other) return *this;
    ::inet::EtherTraffic::operator=(other);
    copy(other);
    return *this;
}

void EtherJam::copy(const EtherJam& other)
{
    this->abortedPkTreeID = other.abortedPkTreeID;
}

void EtherJam::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherTraffic::parsimPack(b);
    doParsimPacking(b,this->abortedPkTreeID);
}

void EtherJam::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherTraffic::parsimUnpack(b);
    doParsimUnpacking(b,this->abortedPkTreeID);
}

long EtherJam::getAbortedPkTreeID() const
{
    return this->abortedPkTreeID;
}

void EtherJam::setAbortedPkTreeID(long abortedPkTreeID)
{
    this->abortedPkTreeID = abortedPkTreeID;
}

class EtherJamDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherJamDescriptor();
    virtual ~EtherJamDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherJamDescriptor)

EtherJamDescriptor::EtherJamDescriptor() : omnetpp::cClassDescriptor("inet::EtherJam", "inet::EtherTraffic")
{
    propertynames = nullptr;
}

EtherJamDescriptor::~EtherJamDescriptor()
{
    delete[] propertynames;
}

bool EtherJamDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherJam *>(obj)!=nullptr;
}

const char **EtherJamDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherJamDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherJamDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int EtherJamDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EtherJamDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "abortedPkTreeID",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int EtherJamDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "abortedPkTreeID")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherJamDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "long",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **EtherJamDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherJamDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherJamDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherJam *pp = (EtherJam *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherJamDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherJam *pp = (EtherJam *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherJamDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherJam *pp = (EtherJam *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getAbortedPkTreeID());
        default: return "";
    }
}

bool EtherJamDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherJam *pp = (EtherJam *)object; (void)pp;
    switch (field) {
        case 0: pp->setAbortedPkTreeID(string2long(value)); return true;
        default: return false;
    }
}

const char *EtherJamDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EtherJamDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherJam *pp = (EtherJam *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EtherFilledIFG)

EtherFilledIFG::EtherFilledIFG(const char *name, short kind) : ::inet::EtherTraffic(name,kind)
{
    this->setBitLength(INTERFRAME_GAP_BITS);
}

EtherFilledIFG::EtherFilledIFG(const EtherFilledIFG& other) : ::inet::EtherTraffic(other)
{
    copy(other);
}

EtherFilledIFG::~EtherFilledIFG()
{
}

EtherFilledIFG& EtherFilledIFG::operator=(const EtherFilledIFG& other)
{
    if (this==&other) return *this;
    ::inet::EtherTraffic::operator=(other);
    copy(other);
    return *this;
}

void EtherFilledIFG::copy(const EtherFilledIFG& other)
{
}

void EtherFilledIFG::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherTraffic::parsimPack(b);
}

void EtherFilledIFG::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherTraffic::parsimUnpack(b);
}

class EtherFilledIFGDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherFilledIFGDescriptor();
    virtual ~EtherFilledIFGDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherFilledIFGDescriptor)

EtherFilledIFGDescriptor::EtherFilledIFGDescriptor() : omnetpp::cClassDescriptor("inet::EtherFilledIFG", "inet::EtherTraffic")
{
    propertynames = nullptr;
}

EtherFilledIFGDescriptor::~EtherFilledIFGDescriptor()
{
    delete[] propertynames;
}

bool EtherFilledIFGDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherFilledIFG *>(obj)!=nullptr;
}

const char **EtherFilledIFGDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherFilledIFGDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherFilledIFGDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int EtherFilledIFGDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *EtherFilledIFGDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int EtherFilledIFGDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherFilledIFGDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **EtherFilledIFGDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherFilledIFGDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherFilledIFGDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherFilledIFG *pp = (EtherFilledIFG *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherFilledIFGDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFilledIFG *pp = (EtherFilledIFG *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherFilledIFGDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFilledIFG *pp = (EtherFilledIFG *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool EtherFilledIFGDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherFilledIFG *pp = (EtherFilledIFG *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *EtherFilledIFGDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *EtherFilledIFGDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherFilledIFG *pp = (EtherFilledIFG *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

EtherPhyFrame_Base::EtherPhyFrame_Base(const char *name, short kind) : ::inet::EtherTraffic(name,kind)
{
    this->setByteLength(PREAMBLE_BYTES + SFD_BYTES);

    this->srcMacFullDuplex = false;
}

EtherPhyFrame_Base::EtherPhyFrame_Base(const EtherPhyFrame_Base& other) : ::inet::EtherTraffic(other)
{
    copy(other);
}

EtherPhyFrame_Base::~EtherPhyFrame_Base()
{
}

EtherPhyFrame_Base& EtherPhyFrame_Base::operator=(const EtherPhyFrame_Base& other)
{
    if (this==&other) return *this;
    ::inet::EtherTraffic::operator=(other);
    copy(other);
    return *this;
}

void EtherPhyFrame_Base::copy(const EtherPhyFrame_Base& other)
{
    this->srcMacFullDuplex = other.srcMacFullDuplex;
}

void EtherPhyFrame_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherTraffic::parsimPack(b);
    doParsimPacking(b,this->srcMacFullDuplex);
}

void EtherPhyFrame_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherTraffic::parsimUnpack(b);
    doParsimUnpacking(b,this->srcMacFullDuplex);
}

bool EtherPhyFrame_Base::getSrcMacFullDuplex() const
{
    return this->srcMacFullDuplex;
}

void EtherPhyFrame_Base::setSrcMacFullDuplex(bool srcMacFullDuplex)
{
    this->srcMacFullDuplex = srcMacFullDuplex;
}

class EtherPhyFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherPhyFrameDescriptor();
    virtual ~EtherPhyFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherPhyFrameDescriptor)

EtherPhyFrameDescriptor::EtherPhyFrameDescriptor() : omnetpp::cClassDescriptor("inet::EtherPhyFrame", "inet::EtherTraffic")
{
    propertynames = nullptr;
}

EtherPhyFrameDescriptor::~EtherPhyFrameDescriptor()
{
    delete[] propertynames;
}

bool EtherPhyFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherPhyFrame_Base *>(obj)!=nullptr;
}

const char **EtherPhyFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherPhyFrameDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherPhyFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int EtherPhyFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EtherPhyFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcMacFullDuplex",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int EtherPhyFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcMacFullDuplex")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherPhyFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **EtherPhyFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherPhyFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherPhyFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherPhyFrame_Base *pp = (EtherPhyFrame_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherPhyFrameDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherPhyFrame_Base *pp = (EtherPhyFrame_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherPhyFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherPhyFrame_Base *pp = (EtherPhyFrame_Base *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getSrcMacFullDuplex());
        default: return "";
    }
}

bool EtherPhyFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherPhyFrame_Base *pp = (EtherPhyFrame_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcMacFullDuplex(string2bool(value)); return true;
        default: return false;
    }
}

const char *EtherPhyFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EtherPhyFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherPhyFrame_Base *pp = (EtherPhyFrame_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EtherFrame)

EtherFrame::EtherFrame(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

EtherFrame::EtherFrame(const EtherFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EtherFrame::~EtherFrame()
{
}

EtherFrame& EtherFrame::operator=(const EtherFrame& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EtherFrame::copy(const EtherFrame& other)
{
    this->dest = other.dest;
    this->src = other.src;
}

void EtherFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->dest);
    doParsimPacking(b,this->src);
}

void EtherFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->dest);
    doParsimUnpacking(b,this->src);
}

MACAddress& EtherFrame::getDest()
{
    return this->dest;
}

void EtherFrame::setDest(const MACAddress& dest)
{
    this->dest = dest;
}

MACAddress& EtherFrame::getSrc()
{
    return this->src;
}

void EtherFrame::setSrc(const MACAddress& src)
{
    this->src = src;
}

class EtherFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherFrameDescriptor();
    virtual ~EtherFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherFrameDescriptor)

EtherFrameDescriptor::EtherFrameDescriptor() : omnetpp::cClassDescriptor("inet::EtherFrame", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

EtherFrameDescriptor::~EtherFrameDescriptor()
{
    delete[] propertynames;
}

bool EtherFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherFrame *>(obj)!=nullptr;
}

const char **EtherFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int EtherFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *EtherFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dest",
        "src",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int EtherFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "MACAddress",
        "MACAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **EtherFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherFrame *pp = (EtherFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherFrameDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFrame *pp = (EtherFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFrame *pp = (EtherFrame *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDest(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSrc(); return out.str();}
        default: return "";
    }
}

bool EtherFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherFrame *pp = (EtherFrame *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *EtherFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(MACAddress));
        case 1: return omnetpp::opp_typename(typeid(MACAddress));
        default: return nullptr;
    };
}

void *EtherFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherFrame *pp = (EtherFrame *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDest()); break;
        case 1: return (void *)(&pp->getSrc()); break;
        default: return nullptr;
    }
}

Register_Class(EthernetIIFrame)

EthernetIIFrame::EthernetIIFrame(const char *name, short kind) : ::inet::EtherFrame(name,kind)
{
    this->setByteLength(ETHER_MAC_FRAME_BYTES);

    this->etherType = 0;
}

EthernetIIFrame::EthernetIIFrame(const EthernetIIFrame& other) : ::inet::EtherFrame(other)
{
    copy(other);
}

EthernetIIFrame::~EthernetIIFrame()
{
}

EthernetIIFrame& EthernetIIFrame::operator=(const EthernetIIFrame& other)
{
    if (this==&other) return *this;
    ::inet::EtherFrame::operator=(other);
    copy(other);
    return *this;
}

void EthernetIIFrame::copy(const EthernetIIFrame& other)
{
    this->etherType = other.etherType;
}

void EthernetIIFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherFrame::parsimPack(b);
    doParsimPacking(b,this->etherType);
}

void EthernetIIFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->etherType);
}

int EthernetIIFrame::getEtherType() const
{
    return this->etherType;
}

void EthernetIIFrame::setEtherType(int etherType)
{
    this->etherType = etherType;
}

class EthernetIIFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EthernetIIFrameDescriptor();
    virtual ~EthernetIIFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EthernetIIFrameDescriptor)

EthernetIIFrameDescriptor::EthernetIIFrameDescriptor() : omnetpp::cClassDescriptor("inet::EthernetIIFrame", "inet::EtherFrame")
{
    propertynames = nullptr;
}

EthernetIIFrameDescriptor::~EthernetIIFrameDescriptor()
{
    delete[] propertynames;
}

bool EthernetIIFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetIIFrame *>(obj)!=nullptr;
}

const char **EthernetIIFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EthernetIIFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EthernetIIFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int EthernetIIFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EthernetIIFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "etherType",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int EthernetIIFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "etherType")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EthernetIIFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **EthernetIIFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *EthernetIIFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "inet::EtherType";
            return nullptr;
        default: return nullptr;
    }
}

int EthernetIIFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EthernetIIFrame *pp = (EthernetIIFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EthernetIIFrameDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EthernetIIFrame *pp = (EthernetIIFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetIIFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EthernetIIFrame *pp = (EthernetIIFrame *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getEtherType(), "inet::EtherType");
        default: return "";
    }
}

bool EthernetIIFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EthernetIIFrame *pp = (EthernetIIFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setEtherType((inet::EtherType)string2enum(value, "inet::EtherType")); return true;
        default: return false;
    }
}

const char *EthernetIIFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EthernetIIFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EthernetIIFrame *pp = (EthernetIIFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EtherFrameWithLLC)

EtherFrameWithLLC::EtherFrameWithLLC(const char *name, short kind) : ::inet::EtherFrame(name,kind)
{
    this->setByteLength(ETHER_MAC_FRAME_BYTES + ETHER_LLC_HEADER_LENGTH);

    this->dsap = 0;
    this->ssap = 0;
    this->control = 0;
}

EtherFrameWithLLC::EtherFrameWithLLC(const EtherFrameWithLLC& other) : ::inet::EtherFrame(other)
{
    copy(other);
}

EtherFrameWithLLC::~EtherFrameWithLLC()
{
}

EtherFrameWithLLC& EtherFrameWithLLC::operator=(const EtherFrameWithLLC& other)
{
    if (this==&other) return *this;
    ::inet::EtherFrame::operator=(other);
    copy(other);
    return *this;
}

void EtherFrameWithLLC::copy(const EtherFrameWithLLC& other)
{
    this->dsap = other.dsap;
    this->ssap = other.ssap;
    this->control = other.control;
}

void EtherFrameWithLLC::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherFrame::parsimPack(b);
    doParsimPacking(b,this->dsap);
    doParsimPacking(b,this->ssap);
    doParsimPacking(b,this->control);
}

void EtherFrameWithLLC::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->dsap);
    doParsimUnpacking(b,this->ssap);
    doParsimUnpacking(b,this->control);
}

int EtherFrameWithLLC::getDsap() const
{
    return this->dsap;
}

void EtherFrameWithLLC::setDsap(int dsap)
{
    this->dsap = dsap;
}

int EtherFrameWithLLC::getSsap() const
{
    return this->ssap;
}

void EtherFrameWithLLC::setSsap(int ssap)
{
    this->ssap = ssap;
}

int EtherFrameWithLLC::getControl() const
{
    return this->control;
}

void EtherFrameWithLLC::setControl(int control)
{
    this->control = control;
}

class EtherFrameWithLLCDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherFrameWithLLCDescriptor();
    virtual ~EtherFrameWithLLCDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherFrameWithLLCDescriptor)

EtherFrameWithLLCDescriptor::EtherFrameWithLLCDescriptor() : omnetpp::cClassDescriptor("inet::EtherFrameWithLLC", "inet::EtherFrame")
{
    propertynames = nullptr;
}

EtherFrameWithLLCDescriptor::~EtherFrameWithLLCDescriptor()
{
    delete[] propertynames;
}

bool EtherFrameWithLLCDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherFrameWithLLC *>(obj)!=nullptr;
}

const char **EtherFrameWithLLCDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherFrameWithLLCDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherFrameWithLLCDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int EtherFrameWithLLCDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *EtherFrameWithLLCDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dsap",
        "ssap",
        "control",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int EtherFrameWithLLCDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dsap")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "ssap")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "control")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherFrameWithLLCDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **EtherFrameWithLLCDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherFrameWithLLCDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherFrameWithLLCDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithLLC *pp = (EtherFrameWithLLC *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherFrameWithLLCDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithLLC *pp = (EtherFrameWithLLC *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherFrameWithLLCDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithLLC *pp = (EtherFrameWithLLC *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getDsap());
        case 1: return long2string(pp->getSsap());
        case 2: return long2string(pp->getControl());
        default: return "";
    }
}

bool EtherFrameWithLLCDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithLLC *pp = (EtherFrameWithLLC *)object; (void)pp;
    switch (field) {
        case 0: pp->setDsap(string2long(value)); return true;
        case 1: pp->setSsap(string2long(value)); return true;
        case 2: pp->setControl(string2long(value)); return true;
        default: return false;
    }
}

const char *EtherFrameWithLLCDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EtherFrameWithLLCDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithLLC *pp = (EtherFrameWithLLC *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EtherFrameWithSNAP)

EtherFrameWithSNAP::EtherFrameWithSNAP(const char *name, short kind) : ::inet::EtherFrameWithLLC(name,kind)
{
    this->setByteLength(ETHER_MAC_FRAME_BYTES + ETHER_LLC_HEADER_LENGTH + ETHER_SNAP_HEADER_LENGTH);
    this->setDsap(0xAA);
    this->setSsap(0xAA);
    this->setControl(0x03);

    this->orgCode = 0;
    this->localcode = 0;
}

EtherFrameWithSNAP::EtherFrameWithSNAP(const EtherFrameWithSNAP& other) : ::inet::EtherFrameWithLLC(other)
{
    copy(other);
}

EtherFrameWithSNAP::~EtherFrameWithSNAP()
{
}

EtherFrameWithSNAP& EtherFrameWithSNAP::operator=(const EtherFrameWithSNAP& other)
{
    if (this==&other) return *this;
    ::inet::EtherFrameWithLLC::operator=(other);
    copy(other);
    return *this;
}

void EtherFrameWithSNAP::copy(const EtherFrameWithSNAP& other)
{
    this->orgCode = other.orgCode;
    this->localcode = other.localcode;
}

void EtherFrameWithSNAP::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherFrameWithLLC::parsimPack(b);
    doParsimPacking(b,this->orgCode);
    doParsimPacking(b,this->localcode);
}

void EtherFrameWithSNAP::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherFrameWithLLC::parsimUnpack(b);
    doParsimUnpacking(b,this->orgCode);
    doParsimUnpacking(b,this->localcode);
}

int EtherFrameWithSNAP::getOrgCode() const
{
    return this->orgCode;
}

void EtherFrameWithSNAP::setOrgCode(int orgCode)
{
    this->orgCode = orgCode;
}

int EtherFrameWithSNAP::getLocalcode() const
{
    return this->localcode;
}

void EtherFrameWithSNAP::setLocalcode(int localcode)
{
    this->localcode = localcode;
}

class EtherFrameWithSNAPDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherFrameWithSNAPDescriptor();
    virtual ~EtherFrameWithSNAPDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherFrameWithSNAPDescriptor)

EtherFrameWithSNAPDescriptor::EtherFrameWithSNAPDescriptor() : omnetpp::cClassDescriptor("inet::EtherFrameWithSNAP", "inet::EtherFrameWithLLC")
{
    propertynames = nullptr;
}

EtherFrameWithSNAPDescriptor::~EtherFrameWithSNAPDescriptor()
{
    delete[] propertynames;
}

bool EtherFrameWithSNAPDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherFrameWithSNAP *>(obj)!=nullptr;
}

const char **EtherFrameWithSNAPDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherFrameWithSNAPDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherFrameWithSNAPDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int EtherFrameWithSNAPDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *EtherFrameWithSNAPDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "orgCode",
        "localcode",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int EtherFrameWithSNAPDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "orgCode")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "localcode")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherFrameWithSNAPDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **EtherFrameWithSNAPDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherFrameWithSNAPDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherFrameWithSNAPDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithSNAP *pp = (EtherFrameWithSNAP *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherFrameWithSNAPDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithSNAP *pp = (EtherFrameWithSNAP *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherFrameWithSNAPDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithSNAP *pp = (EtherFrameWithSNAP *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getOrgCode());
        case 1: return long2string(pp->getLocalcode());
        default: return "";
    }
}

bool EtherFrameWithSNAPDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithSNAP *pp = (EtherFrameWithSNAP *)object; (void)pp;
    switch (field) {
        case 0: pp->setOrgCode(string2long(value)); return true;
        case 1: pp->setLocalcode(string2long(value)); return true;
        default: return false;
    }
}

const char *EtherFrameWithSNAPDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EtherFrameWithSNAPDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherFrameWithSNAP *pp = (EtherFrameWithSNAP *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EtherPauseFrame)

EtherPauseFrame::EtherPauseFrame(const char *name, short kind) : ::inet::EtherFrame(name,kind)
{
    this->pauseTime = 0;
}

EtherPauseFrame::EtherPauseFrame(const EtherPauseFrame& other) : ::inet::EtherFrame(other)
{
    copy(other);
}

EtherPauseFrame::~EtherPauseFrame()
{
}

EtherPauseFrame& EtherPauseFrame::operator=(const EtherPauseFrame& other)
{
    if (this==&other) return *this;
    ::inet::EtherFrame::operator=(other);
    copy(other);
    return *this;
}

void EtherPauseFrame::copy(const EtherPauseFrame& other)
{
    this->pauseTime = other.pauseTime;
}

void EtherPauseFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::EtherFrame::parsimPack(b);
    doParsimPacking(b,this->pauseTime);
}

void EtherPauseFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::EtherFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->pauseTime);
}

int EtherPauseFrame::getPauseTime() const
{
    return this->pauseTime;
}

void EtherPauseFrame::setPauseTime(int pauseTime)
{
    this->pauseTime = pauseTime;
}

class EtherPauseFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EtherPauseFrameDescriptor();
    virtual ~EtherPauseFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EtherPauseFrameDescriptor)

EtherPauseFrameDescriptor::EtherPauseFrameDescriptor() : omnetpp::cClassDescriptor("inet::EtherPauseFrame", "inet::EtherFrame")
{
    propertynames = nullptr;
}

EtherPauseFrameDescriptor::~EtherPauseFrameDescriptor()
{
    delete[] propertynames;
}

bool EtherPauseFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EtherPauseFrame *>(obj)!=nullptr;
}

const char **EtherPauseFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EtherPauseFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EtherPauseFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int EtherPauseFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EtherPauseFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pauseTime",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int EtherPauseFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pauseTime")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EtherPauseFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **EtherPauseFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EtherPauseFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EtherPauseFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EtherPauseFrame *pp = (EtherPauseFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EtherPauseFrameDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherPauseFrame *pp = (EtherPauseFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EtherPauseFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EtherPauseFrame *pp = (EtherPauseFrame *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPauseTime());
        default: return "";
    }
}

bool EtherPauseFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EtherPauseFrame *pp = (EtherPauseFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setPauseTime(string2long(value)); return true;
        default: return false;
    }
}

const char *EtherPauseFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EtherPauseFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EtherPauseFrame *pp = (EtherPauseFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ethernet1QTag)

Ethernet1QTag::Ethernet1QTag(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->pcp = 0;
    this->de = false;
    this->VID = 0;
}

Ethernet1QTag::Ethernet1QTag(const Ethernet1QTag& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Ethernet1QTag::~Ethernet1QTag()
{
}

Ethernet1QTag& Ethernet1QTag::operator=(const Ethernet1QTag& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Ethernet1QTag::copy(const Ethernet1QTag& other)
{
    this->pcp = other.pcp;
    this->de = other.de;
    this->VID = other.VID;
}

void Ethernet1QTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->pcp);
    doParsimPacking(b,this->de);
    doParsimPacking(b,this->VID);
}

void Ethernet1QTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->pcp);
    doParsimUnpacking(b,this->de);
    doParsimUnpacking(b,this->VID);
}

uint8_t Ethernet1QTag::getPcp() const
{
    return this->pcp;
}

void Ethernet1QTag::setPcp(uint8_t pcp)
{
    this->pcp = pcp;
}

bool Ethernet1QTag::getDe() const
{
    return this->de;
}

void Ethernet1QTag::setDe(bool de)
{
    this->de = de;
}

short Ethernet1QTag::getVID() const
{
    return this->VID;
}

void Ethernet1QTag::setVID(short VID)
{
    this->VID = VID;
}

class Ethernet1QTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Ethernet1QTagDescriptor();
    virtual ~Ethernet1QTagDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(Ethernet1QTagDescriptor)

Ethernet1QTagDescriptor::Ethernet1QTagDescriptor() : omnetpp::cClassDescriptor("inet::Ethernet1QTag", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

Ethernet1QTagDescriptor::~Ethernet1QTagDescriptor()
{
    delete[] propertynames;
}

bool Ethernet1QTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ethernet1QTag *>(obj)!=nullptr;
}

const char **Ethernet1QTagDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ethernet1QTagDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ethernet1QTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int Ethernet1QTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *Ethernet1QTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pcp",
        "de",
        "VID",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int Ethernet1QTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pcp")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "de")==0) return base+1;
    if (fieldName[0]=='V' && strcmp(fieldName, "VID")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ethernet1QTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",
        "bool",
        "short",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ethernet1QTagDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ethernet1QTagDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ethernet1QTagDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ethernet1QTag *pp = (Ethernet1QTag *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ethernet1QTagDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ethernet1QTag *pp = (Ethernet1QTag *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ethernet1QTagDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ethernet1QTag *pp = (Ethernet1QTag *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPcp());
        case 1: return bool2string(pp->getDe());
        case 2: return long2string(pp->getVID());
        default: return "";
    }
}

bool Ethernet1QTagDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ethernet1QTag *pp = (Ethernet1QTag *)object; (void)pp;
    switch (field) {
        case 0: pp->setPcp(string2ulong(value)); return true;
        case 1: pp->setDe(string2bool(value)); return true;
        case 2: pp->setVID(string2long(value)); return true;
        default: return false;
    }
}

const char *Ethernet1QTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ethernet1QTagDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ethernet1QTag *pp = (Ethernet1QTag *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ethernet1ahITag)

Ethernet1ahITag::Ethernet1ahITag(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->ISid = 0;
}

Ethernet1ahITag::Ethernet1ahITag(const Ethernet1ahITag& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Ethernet1ahITag::~Ethernet1ahITag()
{
}

Ethernet1ahITag& Ethernet1ahITag::operator=(const Ethernet1ahITag& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Ethernet1ahITag::copy(const Ethernet1ahITag& other)
{
    this->ISid = other.ISid;
}

void Ethernet1ahITag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->ISid);
}

void Ethernet1ahITag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->ISid);
}

int Ethernet1ahITag::getISid() const
{
    return this->ISid;
}

void Ethernet1ahITag::setISid(int ISid)
{
    this->ISid = ISid;
}

class Ethernet1ahITagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Ethernet1ahITagDescriptor();
    virtual ~Ethernet1ahITagDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(Ethernet1ahITagDescriptor)

Ethernet1ahITagDescriptor::Ethernet1ahITagDescriptor() : omnetpp::cClassDescriptor("inet::Ethernet1ahITag", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

Ethernet1ahITagDescriptor::~Ethernet1ahITagDescriptor()
{
    delete[] propertynames;
}

bool Ethernet1ahITagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ethernet1ahITag *>(obj)!=nullptr;
}

const char **Ethernet1ahITagDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ethernet1ahITagDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ethernet1ahITagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Ethernet1ahITagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *Ethernet1ahITagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ISid",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int Ethernet1ahITagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='I' && strcmp(fieldName, "ISid")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ethernet1ahITagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ethernet1ahITagDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ethernet1ahITagDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ethernet1ahITagDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ethernet1ahITag *pp = (Ethernet1ahITag *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ethernet1ahITagDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ethernet1ahITag *pp = (Ethernet1ahITag *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ethernet1ahITagDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ethernet1ahITag *pp = (Ethernet1ahITag *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getISid());
        default: return "";
    }
}

bool Ethernet1ahITagDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ethernet1ahITag *pp = (Ethernet1ahITag *)object; (void)pp;
    switch (field) {
        case 0: pp->setISid(string2long(value)); return true;
        default: return false;
    }
}

const char *Ethernet1ahITagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ethernet1ahITagDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ethernet1ahITag *pp = (Ethernet1ahITag *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet

