#include "ns3module.h"
static PyMethodDef traffic_control_FatalImpl_functions[] = {
    {NULL, NULL, 0, NULL}
};
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef traffic_control_FatalImpl_moduledef = {
    PyModuleDef_HEAD_INIT,
    "traffic_control.FatalImpl",
    NULL,
    -1,
    traffic_control_FatalImpl_functions,
};
#endif

static PyObject *
inittraffic_control_FatalImpl(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&traffic_control_FatalImpl_moduledef);
    #else
    m = Py_InitModule3((char *) "traffic_control.FatalImpl", traffic_control_FatalImpl_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    return m;
}
static PyMethodDef traffic_control_Hash_Function_functions[] = {
    {NULL, NULL, 0, NULL}
};
/* --- classes --- */


PyTypeObject *_PyNs3HashFunctionFnv1a_Type;


PyTypeObject *_PyNs3HashFunctionHash32_Type;


PyTypeObject *_PyNs3HashFunctionHash64_Type;


PyTypeObject *_PyNs3HashFunctionMurmur3_Type;

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef traffic_control_Hash_Function_moduledef = {
    PyModuleDef_HEAD_INIT,
    "traffic_control.Hash.Function",
    NULL,
    -1,
    traffic_control_Hash_Function_functions,
};
#endif

static PyObject *
inittraffic_control_Hash_Function(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&traffic_control_Hash_Function_moduledef);
    #else
    m = Py_InitModule3((char *) "traffic_control.Hash.Function", traffic_control_Hash_Function_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    /* Import the 'ns3::Hash::Function::Fnv1a' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return NULL;
        }
        _PyNs3HashFunctionFnv1a_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Fnv1a");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Hash::Function::Hash32' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return NULL;
        }
        _PyNs3HashFunctionHash32_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Hash32");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Hash::Function::Hash64' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return NULL;
        }
        _PyNs3HashFunctionHash64_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Hash64");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Hash::Function::Murmur3' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return NULL;
        }
        _PyNs3HashFunctionMurmur3_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Murmur3");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    return m;
}
static PyMethodDef traffic_control_Hash_functions[] = {
    {NULL, NULL, 0, NULL}
};
/* --- classes --- */


PyTypeObject *_PyNs3HashImplementation_Type;

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef traffic_control_Hash_moduledef = {
    PyModuleDef_HEAD_INIT,
    "traffic_control.Hash",
    NULL,
    -1,
    traffic_control_Hash_functions,
};
#endif

static PyObject *
inittraffic_control_Hash(void)
{
    PyObject *m;
    PyObject *submodule;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&traffic_control_Hash_moduledef);
    #else
    m = Py_InitModule3((char *) "traffic_control.Hash", traffic_control_Hash_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    /* Import the 'ns3::Hash::Implementation' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return NULL;
        }
        _PyNs3HashImplementation_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Implementation");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    submodule = inittraffic_control_Hash_Function();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "Function", submodule);
    return m;
}
static PyMethodDef traffic_control_TracedValueCallback_functions[] = {
    {NULL, NULL, 0, NULL}
};
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef traffic_control_TracedValueCallback_moduledef = {
    PyModuleDef_HEAD_INIT,
    "traffic_control.TracedValueCallback",
    NULL,
    -1,
    traffic_control_TracedValueCallback_functions,
};
#endif

static PyObject *
inittraffic_control_TracedValueCallback(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&traffic_control_TracedValueCallback_moduledef);
    #else
    m = Py_InitModule3((char *) "traffic_control.TracedValueCallback", traffic_control_TracedValueCallback_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    return m;
}
static PyMethodDef traffic_control_internal_functions[] = {
    {NULL, NULL, 0, NULL}
};
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef traffic_control_internal_moduledef = {
    PyModuleDef_HEAD_INIT,
    "traffic_control.internal",
    NULL,
    -1,
    traffic_control_internal_functions,
};
#endif

static PyObject *
inittraffic_control_internal(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&traffic_control_internal_moduledef);
    #else
    m = Py_InitModule3((char *) "traffic_control.internal", traffic_control_internal_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    return m;
}
static PyMethodDef traffic_control_functions[] = {
    {NULL, NULL, 0, NULL}
};
/* --- classes --- */


PyTypeObject *_PyNs3Address_Type;
std::map<void*, PyObject*> *_PyNs3Address_wrapper_registry;


PyTypeObject *_PyNs3AttributeConstructionList_Type;
std::map<void*, PyObject*> *_PyNs3AttributeConstructionList_wrapper_registry;


PyTypeObject *_PyNs3AttributeConstructionListItem_Type;
std::map<void*, PyObject*> *_PyNs3AttributeConstructionListItem_wrapper_registry;


PyTypeObject *_PyNs3Buffer_Type;
std::map<void*, PyObject*> *_PyNs3Buffer_wrapper_registry;


PyTypeObject *_PyNs3BufferIterator_Type;
std::map<void*, PyObject*> *_PyNs3BufferIterator_wrapper_registry;


PyTypeObject *_PyNs3ByteTagIterator_Type;
std::map<void*, PyObject*> *_PyNs3ByteTagIterator_wrapper_registry;


PyTypeObject *_PyNs3ByteTagIteratorItem_Type;
std::map<void*, PyObject*> *_PyNs3ByteTagIteratorItem_wrapper_registry;


PyTypeObject *_PyNs3ByteTagList_Type;
std::map<void*, PyObject*> *_PyNs3ByteTagList_wrapper_registry;


PyTypeObject *_PyNs3ByteTagListIterator_Type;
std::map<void*, PyObject*> *_PyNs3ByteTagListIterator_wrapper_registry;


PyTypeObject *_PyNs3ByteTagListIteratorItem_Type;
std::map<void*, PyObject*> *_PyNs3ByteTagListIteratorItem_wrapper_registry;


PyTypeObject *_PyNs3CallbackBase_Type;
std::map<void*, PyObject*> *_PyNs3CallbackBase_wrapper_registry;


PyTypeObject *_PyNs3DataRate_Type;
std::map<void*, PyObject*> *_PyNs3DataRate_wrapper_registry;


PyTypeObject *_PyNs3EventId_Type;
std::map<void*, PyObject*> *_PyNs3EventId_wrapper_registry;


PyTypeObject *_PyNs3Hasher_Type;
std::map<void*, PyObject*> *_PyNs3Hasher_wrapper_registry;


PyTypeObject *_PyNs3IntToType__0_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__0_wrapper_registry;


PyTypeObject *_PyNs3IntToType__1_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__1_wrapper_registry;


PyTypeObject *_PyNs3IntToType__2_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__2_wrapper_registry;


PyTypeObject *_PyNs3IntToType__3_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__3_wrapper_registry;


PyTypeObject *_PyNs3IntToType__4_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__4_wrapper_registry;


PyTypeObject *_PyNs3IntToType__5_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__5_wrapper_registry;


PyTypeObject *_PyNs3IntToType__6_Type;
std::map<void*, PyObject*> *_PyNs3IntToType__6_wrapper_registry;


PyTypeObject *_PyNs3Ipv4Address_Type;
std::map<void*, PyObject*> *_PyNs3Ipv4Address_wrapper_registry;


PyTypeObject *_PyNs3Ipv4Mask_Type;
std::map<void*, PyObject*> *_PyNs3Ipv4Mask_wrapper_registry;


PyTypeObject *_PyNs3Ipv6Address_Type;
std::map<void*, PyObject*> *_PyNs3Ipv6Address_wrapper_registry;


PyTypeObject *_PyNs3Ipv6Prefix_Type;
std::map<void*, PyObject*> *_PyNs3Ipv6Prefix_wrapper_registry;


PyTypeObject *_PyNs3Mac48Address_Type;
std::map<void*, PyObject*> *_PyNs3Mac48Address_wrapper_registry;


PyTypeObject *_PyNs3NetDeviceContainer_Type;
std::map<void*, PyObject*> *_PyNs3NetDeviceContainer_wrapper_registry;


PyTypeObject *_PyNs3ObjectBase_Type;
std::map<void*, PyObject*> *_PyNs3ObjectBase_wrapper_registry;


PyTypeObject *_PyNs3ObjectDeleter_Type;
std::map<void*, PyObject*> *_PyNs3ObjectDeleter_wrapper_registry;


PyTypeObject *_PyNs3ObjectFactory_Type;
std::map<void*, PyObject*> *_PyNs3ObjectFactory_wrapper_registry;


PyTypeObject *_PyNs3PacketMetadata_Type;
std::map<void*, PyObject*> *_PyNs3PacketMetadata_wrapper_registry;


PyTypeObject *_PyNs3PacketMetadataItem_Type;
std::map<void*, PyObject*> *_PyNs3PacketMetadataItem_wrapper_registry;


PyTypeObject *_PyNs3PacketMetadataItemIterator_Type;
std::map<void*, PyObject*> *_PyNs3PacketMetadataItemIterator_wrapper_registry;


PyTypeObject *_PyNs3PacketTagIterator_Type;
std::map<void*, PyObject*> *_PyNs3PacketTagIterator_wrapper_registry;


PyTypeObject *_PyNs3PacketTagIteratorItem_Type;
std::map<void*, PyObject*> *_PyNs3PacketTagIteratorItem_wrapper_registry;


PyTypeObject *_PyNs3PacketTagList_Type;
std::map<void*, PyObject*> *_PyNs3PacketTagList_wrapper_registry;


PyTypeObject *_PyNs3PacketTagListTagData_Type;
std::map<void*, PyObject*> *_PyNs3PacketTagListTagData_wrapper_registry;


PyTypeObject *_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map;


PyTypeObject *_PyNs3Simulator_Type;
std::map<void*, PyObject*> *_PyNs3Simulator_wrapper_registry;


PyTypeObject *_PyNs3Tag_Type;


PyTypeObject *_PyNs3TagBuffer_Type;
std::map<void*, PyObject*> *_PyNs3TagBuffer_wrapper_registry;


PyTypeObject *_PyNs3TimeWithUnit_Type;
std::map<void*, PyObject*> *_PyNs3TimeWithUnit_wrapper_registry;


PyTypeObject *_PyNs3Timer_Type;
std::map<void*, PyObject*> *_PyNs3Timer_wrapper_registry;


PyTypeObject *_PyNs3TimerImpl_Type;
std::map<void*, PyObject*> *_PyNs3TimerImpl_wrapper_registry;


PyTypeObject *_PyNs3TracedValue__Bool_Type;
std::map<void*, PyObject*> *_PyNs3TracedValue__Bool_wrapper_registry;


PyTypeObject *_PyNs3TracedValue__Unsigned_int_Type;
std::map<void*, PyObject*> *_PyNs3TracedValue__Unsigned_int_wrapper_registry;


PyTypeObject *_PyNs3TypeId_Type;
std::map<void*, PyObject*> *_PyNs3TypeId_wrapper_registry;


PyTypeObject *_PyNs3TypeIdAttributeInformation_Type;
std::map<void*, PyObject*> *_PyNs3TypeIdAttributeInformation_wrapper_registry;


PyTypeObject *_PyNs3TypeIdTraceSourceInformation_Type;
std::map<void*, PyObject*> *_PyNs3TypeIdTraceSourceInformation_wrapper_registry;


PyTypeObject *_PyNs3Empty_Type;
std::map<void*, PyObject*> *_PyNs3Empty_wrapper_registry;


PyTypeObject *_PyNs3Int64x64_t_Type;
std::map<void*, PyObject*> *_PyNs3Int64x64_t_wrapper_registry;


PyTypeObject *_PyNs3Chunk_Type;


PyTypeObject *_PyNs3Header_Type;


PyTypeObject *_PyNs3Object_Type;


PyTypeObject *_PyNs3ObjectAggregateIterator_Type;
std::map<void*, PyObject*> *_PyNs3ObjectAggregateIterator_wrapper_registry;


PyTypeObject *_PyNs3Queue_Type;


PyTypeObject *_PyNs3RandomVariableStream_Type;


PyTypeObject *_PyNs3SequentialRandomVariable_Type;


PyTypeObject *_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map;


PyTypeObject *_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___Type;
pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map;


PyTypeObject *_PyNs3Time_Type;
std::map<void*, PyObject*> *_PyNs3Time_wrapper_registry;


PyTypeObject *_PyNs3TraceSourceAccessor_Type;


PyTypeObject *_PyNs3TracedValue__Ns3Time_Type;
std::map<void*, PyObject*> *_PyNs3TracedValue__Ns3Time_wrapper_registry;


PyTypeObject *_PyNs3Trailer_Type;


PyTypeObject *_PyNs3TriangularRandomVariable_Type;


PyTypeObject *_PyNs3UniformRandomVariable_Type;


PyTypeObject *_PyNs3WeibullRandomVariable_Type;


PyTypeObject *_PyNs3ZetaRandomVariable_Type;


PyTypeObject *_PyNs3ZipfRandomVariable_Type;


PyTypeObject *_PyNs3AttributeAccessor_Type;


PyTypeObject *_PyNs3AttributeChecker_Type;


PyTypeObject *_PyNs3AttributeValue_Type;


PyTypeObject *_PyNs3BooleanChecker_Type;


PyTypeObject *_PyNs3BooleanValue_Type;


PyTypeObject *_PyNs3CallbackChecker_Type;


PyTypeObject *_PyNs3CallbackImplBase_Type;


PyTypeObject *_PyNs3CallbackValue_Type;


PyTypeObject *_PyNs3ConstantRandomVariable_Type;


PyTypeObject *_PyNs3DataRateChecker_Type;


PyTypeObject *_PyNs3DataRateValue_Type;


PyTypeObject *_PyNs3DeterministicRandomVariable_Type;


PyTypeObject *_PyNs3DoubleValue_Type;


PyTypeObject *_PyNs3EmpiricalRandomVariable_Type;


PyTypeObject *_PyNs3EmptyAttributeAccessor_Type;


PyTypeObject *_PyNs3EmptyAttributeChecker_Type;


PyTypeObject *_PyNs3EmptyAttributeValue_Type;


PyTypeObject *_PyNs3EnumChecker_Type;


PyTypeObject *_PyNs3EnumValue_Type;


PyTypeObject *_PyNs3ErlangRandomVariable_Type;


PyTypeObject *_PyNs3EventImpl_Type;


PyTypeObject *_PyNs3ExponentialRandomVariable_Type;


PyTypeObject *_PyNs3GammaRandomVariable_Type;


PyTypeObject *_PyNs3IntegerValue_Type;


PyTypeObject *_PyNs3Ipv4AddressChecker_Type;


PyTypeObject *_PyNs3Ipv4AddressValue_Type;


PyTypeObject *_PyNs3Ipv4MaskChecker_Type;


PyTypeObject *_PyNs3Ipv4MaskValue_Type;


PyTypeObject *_PyNs3Ipv6AddressChecker_Type;


PyTypeObject *_PyNs3Ipv6AddressValue_Type;


PyTypeObject *_PyNs3Ipv6PrefixChecker_Type;


PyTypeObject *_PyNs3Ipv6PrefixValue_Type;


PyTypeObject *_PyNs3LogNormalRandomVariable_Type;


PyTypeObject *_PyNs3Mac48AddressChecker_Type;


PyTypeObject *_PyNs3Mac48AddressValue_Type;


PyTypeObject *_PyNs3NetDevice_Type;


PyTypeObject *_PyNs3NetDeviceQueue_Type;


PyTypeObject *_PyNs3NetDeviceQueueInterface_Type;


PyTypeObject *_PyNs3NixVector_Type;


PyTypeObject *_PyNs3Node_Type;


PyTypeObject *_PyNs3NormalRandomVariable_Type;


PyTypeObject *_PyNs3ObjectFactoryChecker_Type;


PyTypeObject *_PyNs3ObjectFactoryValue_Type;


PyTypeObject *_PyNs3Packet_Type;


PyTypeObject *_PyNs3ParetoRandomVariable_Type;


PyTypeObject *_PyNs3QueueItem_Type;


PyTypeObject *_PyNs3StringChecker_Type;


PyTypeObject *_PyNs3StringValue_Type;


PyTypeObject *_PyNs3TimeValue_Type;


PyTypeObject *_PyNs3TypeIdChecker_Type;


PyTypeObject *_PyNs3TypeIdValue_Type;


PyTypeObject *_PyNs3UintegerValue_Type;


PyTypeObject *_PyNs3AddressChecker_Type;


PyTypeObject *_PyNs3AddressValue_Type;


std::map<void*, PyObject*> PyNs3QueueDiscContainer_wrapper_registry;


static int
_wrap_PyNs3QueueDiscContainer__tp_init__0(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3QueueDiscContainer *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscContainer_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::QueueDiscContainer(*((PyNs3QueueDiscContainer *) arg0)->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3QueueDiscContainer__tp_init__1(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::QueueDiscContainer();
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3QueueDiscContainer__tp_init__2(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3QueueDisc *qDisc;
    ns3::QueueDisc *qDisc_ptr;
    const char *keywords[] = {"qDisc", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDisc_Type, &qDisc)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    qDisc_ptr = (qDisc ? qDisc->obj : NULL);
    self->obj = new ns3::QueueDiscContainer(ns3::Ptr< ns3::QueueDisc  > (qDisc_ptr));
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

int _wrap_PyNs3QueueDiscContainer__tp_init(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[3] = {0,};
    retval = _wrap_PyNs3QueueDiscContainer__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3QueueDiscContainer__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    retval = _wrap_PyNs3QueueDiscContainer__tp_init__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }
    error_list = PyList_New(3);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}



PyObject *
_wrap_PyNs3QueueDiscContainer_Add__0(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyObject *py_retval;
    PyNs3QueueDiscContainer *other;
    const char *keywords[] = {"other", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscContainer_Type, &other)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }
    self->obj->Add(*((PyNs3QueueDiscContainer *) other)->obj);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
_wrap_PyNs3QueueDiscContainer_Add__1(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyObject *py_retval;
    PyNs3QueueDisc *qDisc;
    ns3::QueueDisc *qDisc_ptr;
    const char *keywords[] = {"qDisc", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDisc_Type, &qDisc)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }
    qDisc_ptr = (qDisc ? qDisc->obj : NULL);
    self->obj->Add(ns3::Ptr< ns3::QueueDisc  > (qDisc_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject * _wrap_PyNs3QueueDiscContainer_Add(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs)
{
    PyObject * retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3QueueDiscContainer_Add__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3QueueDiscContainer_Add__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return NULL;
}


PyObject *
_wrap_PyNs3QueueDiscContainer_GetN(PyNs3QueueDiscContainer *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetN();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscContainer_Get(PyNs3QueueDiscContainer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDisc > retval;
    unsigned int i;
    const char *keywords[] = {"i", NULL};
    PyNs3QueueDisc *py_QueueDisc;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &i)) {
        return NULL;
    }
    retval = self->obj->Get(i);
    if (!(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3QueueDisc__PythonHelper).name())
    {
        py_QueueDisc = reinterpret_cast< PyNs3QueueDisc* >(reinterpret_cast< PyNs3QueueDisc__PythonHelper* >(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))->m_pyself);
        py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
        Py_INCREF(py_QueueDisc);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDisc = NULL;
        } else {
            py_QueueDisc = (PyNs3QueueDisc *) wrapper_lookup_iter->second;
            Py_INCREF(py_QueueDisc);
        }
    
        if (py_QueueDisc == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))), &PyNs3QueueDisc_Type);
            py_QueueDisc = PyObject_GC_New(PyNs3QueueDisc, wrapper_type);
            py_QueueDisc->inst_dict = NULL;
    
            py_QueueDisc->inst_dict = NULL;
            py_QueueDisc->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval))->Ref();
            py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDisc->obj] = (PyObject *) py_QueueDisc;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDisc);
    return py_retval;
}


static PyObject*
_wrap_PyNs3QueueDiscContainer__copy__(PyNs3QueueDiscContainer *self)
{

    PyNs3QueueDiscContainer *py_copy;
    py_copy = PyObject_New(PyNs3QueueDiscContainer, &PyNs3QueueDiscContainer_Type);
    py_copy->obj = new ns3::QueueDiscContainer(*self->obj);
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3QueueDiscContainer_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3QueueDiscContainer_methods[] = {
    {(char *) "Add", (PyCFunction) _wrap_PyNs3QueueDiscContainer_Add, METH_KEYWORDS|METH_VARARGS, NULL },
    {(char *) "GetN", (PyCFunction) _wrap_PyNs3QueueDiscContainer_GetN, METH_NOARGS, "GetN()\n\n" },
    {(char *) "Get", (PyCFunction) _wrap_PyNs3QueueDiscContainer_Get, METH_KEYWORDS|METH_VARARGS, "Get(i)\n\ntype: i: uint32_t" },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3QueueDiscContainer__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
_wrap_PyNs3QueueDiscContainer__tp_dealloc(PyNs3QueueDiscContainer *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3QueueDiscContainer_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3QueueDiscContainer_wrapper_registry.end()) {
        PyNs3QueueDiscContainer_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
        ns3::QueueDiscContainer *tmp = self->obj;
        self->obj = NULL;
        if (!(self->flags&PYBINDGEN_WRAPPER_FLAG_OBJECT_NOT_OWNED)) {
            delete tmp;
        }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3QueueDiscContainer__tp_richcompare (PyNs3QueueDiscContainer *PYBINDGEN_UNUSED(self), PyNs3QueueDiscContainer *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3QueueDiscContainer_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3QueueDiscContainer_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.QueueDiscContainer",            /* tp_name */
    sizeof(PyNs3QueueDiscContainer),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3QueueDiscContainer__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    "QueueDiscContainer(qDisc)\nQueueDiscContainer(arg0)\nQueueDiscContainer()",                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3QueueDiscContainer__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3QueueDiscContainer_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3QueueDiscContainer__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};



std::map<void*, PyObject*> PyNs3QueueDiscFactory_wrapper_registry;


static int
_wrap_PyNs3QueueDiscFactory__tp_init__0(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3QueueDiscFactory *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscFactory_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::QueueDiscFactory(*((PyNs3QueueDiscFactory *) arg0)->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3QueueDiscFactory__tp_init__1(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3ObjectFactory *factory;
    const char *keywords[] = {"factory", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3ObjectFactory_Type, &factory)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::QueueDiscFactory(*((PyNs3ObjectFactory *) factory)->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

int _wrap_PyNs3QueueDiscFactory__tp_init(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3QueueDiscFactory__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3QueueDiscFactory__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3QueueDiscFactory_CreateQueueDisc(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDisc > retval;
    std::vector< ns3::Ptr< ns3::QueueDisc > > queueDiscs_value;
    const char *keywords[] = {"queueDiscs", NULL};
    PyNs3QueueDisc *py_QueueDisc;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O&", (char **) keywords, _wrap_convert_py2c__std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__, &queueDiscs_value)) {
        return NULL;
    }
    retval = self->obj->CreateQueueDisc(queueDiscs_value);
    if (!(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3QueueDisc__PythonHelper).name())
    {
        py_QueueDisc = reinterpret_cast< PyNs3QueueDisc* >(reinterpret_cast< PyNs3QueueDisc__PythonHelper* >(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))->m_pyself);
        py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
        Py_INCREF(py_QueueDisc);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDisc = NULL;
        } else {
            py_QueueDisc = (PyNs3QueueDisc *) wrapper_lookup_iter->second;
            Py_INCREF(py_QueueDisc);
        }
    
        if (py_QueueDisc == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))), &PyNs3QueueDisc_Type);
            py_QueueDisc = PyObject_GC_New(PyNs3QueueDisc, wrapper_type);
            py_QueueDisc->inst_dict = NULL;
    
            py_QueueDisc->inst_dict = NULL;
            py_QueueDisc->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval))->Ref();
            py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDisc->obj] = (PyObject *) py_QueueDisc;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDisc);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscFactory_AddQueueDiscClass(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    uint16_t retval;
    PyNs3ObjectFactory *factory;
    const char *keywords[] = {"factory", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3ObjectFactory_Type, &factory)) {
        return NULL;
    }
    retval = self->obj->AddQueueDiscClass(*((PyNs3ObjectFactory *) factory)->obj);
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscFactory_SetChildQueueDisc(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int classId;
    int handle;
    const char *keywords[] = {"classId", "handle", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ii", (char **) keywords, &classId, &handle)) {
        return NULL;
    }
    if (classId > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    if (handle > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    self->obj->SetChildQueueDisc(classId, handle);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscFactory_AddPacketFilter(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3ObjectFactory *factory;
    const char *keywords[] = {"factory", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3ObjectFactory_Type, &factory)) {
        return NULL;
    }
    self->obj->AddPacketFilter(*((PyNs3ObjectFactory *) factory)->obj);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscFactory_AddInternalQueue(PyNs3QueueDiscFactory *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3ObjectFactory *factory;
    const char *keywords[] = {"factory", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3ObjectFactory_Type, &factory)) {
        return NULL;
    }
    self->obj->AddInternalQueue(*((PyNs3ObjectFactory *) factory)->obj);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


static PyObject*
_wrap_PyNs3QueueDiscFactory__copy__(PyNs3QueueDiscFactory *self)
{

    PyNs3QueueDiscFactory *py_copy;
    py_copy = PyObject_New(PyNs3QueueDiscFactory, &PyNs3QueueDiscFactory_Type);
    py_copy->obj = new ns3::QueueDiscFactory(*self->obj);
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3QueueDiscFactory_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3QueueDiscFactory_methods[] = {
    {(char *) "CreateQueueDisc", (PyCFunction) _wrap_PyNs3QueueDiscFactory_CreateQueueDisc, METH_KEYWORDS|METH_VARARGS, "CreateQueueDisc(queueDiscs)\n\ntype: queueDiscs: std::vector< ns3::Ptr< ns3::QueueDisc > > const &" },
    {(char *) "AddQueueDiscClass", (PyCFunction) _wrap_PyNs3QueueDiscFactory_AddQueueDiscClass, METH_KEYWORDS|METH_VARARGS, "AddQueueDiscClass(factory)\n\ntype: factory: ns3::ObjectFactory" },
    {(char *) "SetChildQueueDisc", (PyCFunction) _wrap_PyNs3QueueDiscFactory_SetChildQueueDisc, METH_KEYWORDS|METH_VARARGS, "SetChildQueueDisc(classId, handle)\n\ntype: classId: uint16_t\ntype: handle: uint16_t" },
    {(char *) "AddPacketFilter", (PyCFunction) _wrap_PyNs3QueueDiscFactory_AddPacketFilter, METH_KEYWORDS|METH_VARARGS, "AddPacketFilter(factory)\n\ntype: factory: ns3::ObjectFactory" },
    {(char *) "AddInternalQueue", (PyCFunction) _wrap_PyNs3QueueDiscFactory_AddInternalQueue, METH_KEYWORDS|METH_VARARGS, "AddInternalQueue(factory)\n\ntype: factory: ns3::ObjectFactory" },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3QueueDiscFactory__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
_wrap_PyNs3QueueDiscFactory__tp_dealloc(PyNs3QueueDiscFactory *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3QueueDiscFactory_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3QueueDiscFactory_wrapper_registry.end()) {
        PyNs3QueueDiscFactory_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
        ns3::QueueDiscFactory *tmp = self->obj;
        self->obj = NULL;
        if (!(self->flags&PYBINDGEN_WRAPPER_FLAG_OBJECT_NOT_OWNED)) {
            delete tmp;
        }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3QueueDiscFactory__tp_richcompare (PyNs3QueueDiscFactory *PYBINDGEN_UNUSED(self), PyNs3QueueDiscFactory *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3QueueDiscFactory_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3QueueDiscFactory_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.QueueDiscFactory",            /* tp_name */
    sizeof(PyNs3QueueDiscFactory),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3QueueDiscFactory__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    "QueueDiscFactory(factory)\nQueueDiscFactory(arg0)",                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3QueueDiscFactory__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3QueueDiscFactory_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3QueueDiscFactory__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};



std::map<void*, PyObject*> PyNs3TrafficControlHelper_wrapper_registry;


static int
_wrap_PyNs3TrafficControlHelper__tp_init__0(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3TrafficControlHelper *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3TrafficControlHelper_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::TrafficControlHelper(*((PyNs3TrafficControlHelper *) arg0)->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3TrafficControlHelper__tp_init__1(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::TrafficControlHelper();
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

int _wrap_PyNs3TrafficControlHelper__tp_init(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3TrafficControlHelper__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3TrafficControlHelper__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_AddChildQueueDiscs(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int handle;
    std::vector< short unsigned int > classes_value;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *n09 = NULL;
    Py_ssize_t n09_len;
    PyNs3AttributeValue *v09 = NULL;
    ns3::EmptyAttributeValue v09_default = ns3::EmptyAttributeValue();
    const char *n10 = NULL;
    Py_ssize_t n10_len;
    PyNs3AttributeValue *v10 = NULL;
    ns3::EmptyAttributeValue v10_default = ns3::EmptyAttributeValue();
    const char *n11 = NULL;
    Py_ssize_t n11_len;
    PyNs3AttributeValue *v11 = NULL;
    ns3::EmptyAttributeValue v11_default = ns3::EmptyAttributeValue();
    const char *n12 = NULL;
    Py_ssize_t n12_len;
    PyNs3AttributeValue *v12 = NULL;
    ns3::EmptyAttributeValue v12_default = ns3::EmptyAttributeValue();
    const char *n13 = NULL;
    Py_ssize_t n13_len;
    PyNs3AttributeValue *v13 = NULL;
    ns3::EmptyAttributeValue v13_default = ns3::EmptyAttributeValue();
    const char *n14 = NULL;
    Py_ssize_t n14_len;
    PyNs3AttributeValue *v14 = NULL;
    ns3::EmptyAttributeValue v14_default = ns3::EmptyAttributeValue();
    const char *n15 = NULL;
    Py_ssize_t n15_len;
    PyNs3AttributeValue *v15 = NULL;
    ns3::EmptyAttributeValue v15_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"handle", "classes", "type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", "n09", "v09", "n10", "v10", "n11", "v11", "n12", "v12", "n13", "v13", "n14", "v14", "n15", "v15", NULL};
    std::vector< short unsigned int > retval;
    Pystd__vector__lt___short_unsigned_int___gt__ *py_std__vector__lt___short_unsigned_int___gt__;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iO&s#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &handle, _wrap_convert_py2c__std__vector__lt___short_unsigned_int___gt__, &classes_value, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08, &n09, &n09_len, &PyNs3AttributeValue_Type, &v09, &n10, &n10_len, &PyNs3AttributeValue_Type, &v10, &n11, &n11_len, &PyNs3AttributeValue_Type, &v11, &n12, &n12_len, &PyNs3AttributeValue_Type, &v12, &n13, &n13_len, &PyNs3AttributeValue_Type, &v13, &n14, &n14_len, &PyNs3AttributeValue_Type, &v14, &n15, &n15_len, &PyNs3AttributeValue_Type, &v15)) {
        return NULL;
    }
    if (handle > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    retval = self->obj->AddChildQueueDiscs(handle, classes_value, std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default), (n09 ? std::string(n09, n09_len) : ""), (v09 ? (*((PyNs3AttributeValue *) v09)->obj) : v09_default), (n10 ? std::string(n10, n10_len) : ""), (v10 ? (*((PyNs3AttributeValue *) v10)->obj) : v10_default), (n11 ? std::string(n11, n11_len) : ""), (v11 ? (*((PyNs3AttributeValue *) v11)->obj) : v11_default), (n12 ? std::string(n12, n12_len) : ""), (v12 ? (*((PyNs3AttributeValue *) v12)->obj) : v12_default), (n13 ? std::string(n13, n13_len) : ""), (v13 ? (*((PyNs3AttributeValue *) v13)->obj) : v13_default), (n14 ? std::string(n14, n14_len) : ""), (v14 ? (*((PyNs3AttributeValue *) v14)->obj) : v14_default), (n15 ? std::string(n15, n15_len) : ""), (v15 ? (*((PyNs3AttributeValue *) v15)->obj) : v15_default));
    py_std__vector__lt___short_unsigned_int___gt__ = PyObject_New(Pystd__vector__lt___short_unsigned_int___gt__, &Pystd__vector__lt___short_unsigned_int___gt___Type);
    py_std__vector__lt___short_unsigned_int___gt__->obj = new std::vector< short unsigned int >(retval);
    py_retval = Py_BuildValue((char *) "N", py_std__vector__lt___short_unsigned_int___gt__);
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_AddInternalQueues(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int handle;
    int count;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"handle", "count", "type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iis#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &handle, &count, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08)) {
        return NULL;
    }
    if (handle > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    if (count > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    self->obj->AddInternalQueues(handle, count, std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_Default(void)
{
    PyObject *py_retval;
    PyNs3TrafficControlHelper *py_TrafficControlHelper;
    
    ns3::TrafficControlHelper retval = ns3::TrafficControlHelper::Default();
    py_TrafficControlHelper = PyObject_New(PyNs3TrafficControlHelper, &PyNs3TrafficControlHelper_Type);
    py_TrafficControlHelper->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TrafficControlHelper->obj = new ns3::TrafficControlHelper(retval);
    PyNs3TrafficControlHelper_wrapper_registry[(void *) py_TrafficControlHelper->obj] = (PyObject *) py_TrafficControlHelper;
    py_retval = Py_BuildValue((char *) "N", py_TrafficControlHelper);
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_AddQueueDiscClasses(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int handle;
    int count;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"handle", "count", "type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", NULL};
    std::vector< short unsigned int > retval;
    Pystd__vector__lt___short_unsigned_int___gt__ *py_std__vector__lt___short_unsigned_int___gt__;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iis#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &handle, &count, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08)) {
        return NULL;
    }
    if (handle > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    if (count > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    retval = self->obj->AddQueueDiscClasses(handle, count, std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default));
    py_std__vector__lt___short_unsigned_int___gt__ = PyObject_New(Pystd__vector__lt___short_unsigned_int___gt__, &Pystd__vector__lt___short_unsigned_int___gt___Type);
    py_std__vector__lt___short_unsigned_int___gt__->obj = new std::vector< short unsigned int >(retval);
    py_retval = Py_BuildValue((char *) "N", py_std__vector__lt___short_unsigned_int___gt__);
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_AddPacketFilter(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int handle;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"handle", "type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "is#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &handle, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08)) {
        return NULL;
    }
    if (handle > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    self->obj->AddPacketFilter(handle, std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}



PyObject *
_wrap_PyNs3TrafficControlHelper_Install__0(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyObject *py_retval;
    PyNs3NetDeviceContainer *c;
    const char *keywords[] = {"c", NULL};
    PyNs3QueueDiscContainer *py_QueueDiscContainer;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDeviceContainer_Type, &c)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }
    ns3::QueueDiscContainer retval = self->obj->Install(*((PyNs3NetDeviceContainer *) c)->obj);
    py_QueueDiscContainer = PyObject_New(PyNs3QueueDiscContainer, &PyNs3QueueDiscContainer_Type);
    py_QueueDiscContainer->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_QueueDiscContainer->obj = new ns3::QueueDiscContainer(retval);
    PyNs3QueueDiscContainer_wrapper_registry[(void *) py_QueueDiscContainer->obj] = (PyObject *) py_QueueDiscContainer;
    py_retval = Py_BuildValue((char *) "N", py_QueueDiscContainer);
    return py_retval;
}

PyObject *
_wrap_PyNs3TrafficControlHelper_Install__1(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyObject *py_retval;
    PyNs3NetDevice *d;
    ns3::NetDevice *d_ptr;
    const char *keywords[] = {"d", NULL};
    PyNs3QueueDiscContainer *py_QueueDiscContainer;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDevice_Type, &d)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }
    d_ptr = (d ? d->obj : NULL);
    ns3::QueueDiscContainer retval = self->obj->Install(ns3::Ptr< ns3::NetDevice  > (d_ptr));
    py_QueueDiscContainer = PyObject_New(PyNs3QueueDiscContainer, &PyNs3QueueDiscContainer_Type);
    py_QueueDiscContainer->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_QueueDiscContainer->obj = new ns3::QueueDiscContainer(retval);
    PyNs3QueueDiscContainer_wrapper_registry[(void *) py_QueueDiscContainer->obj] = (PyObject *) py_QueueDiscContainer;
    py_retval = Py_BuildValue((char *) "N", py_QueueDiscContainer);
    return py_retval;
}

PyObject * _wrap_PyNs3TrafficControlHelper_Install(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject * retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3TrafficControlHelper_Install__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3TrafficControlHelper_Install__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return NULL;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_SetQueueLimits(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08)) {
        return NULL;
    }
    self->obj->SetQueueLimits(std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_SetRootQueueDisc(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    uint16_t retval;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *n09 = NULL;
    Py_ssize_t n09_len;
    PyNs3AttributeValue *v09 = NULL;
    ns3::EmptyAttributeValue v09_default = ns3::EmptyAttributeValue();
    const char *n10 = NULL;
    Py_ssize_t n10_len;
    PyNs3AttributeValue *v10 = NULL;
    ns3::EmptyAttributeValue v10_default = ns3::EmptyAttributeValue();
    const char *n11 = NULL;
    Py_ssize_t n11_len;
    PyNs3AttributeValue *v11 = NULL;
    ns3::EmptyAttributeValue v11_default = ns3::EmptyAttributeValue();
    const char *n12 = NULL;
    Py_ssize_t n12_len;
    PyNs3AttributeValue *v12 = NULL;
    ns3::EmptyAttributeValue v12_default = ns3::EmptyAttributeValue();
    const char *n13 = NULL;
    Py_ssize_t n13_len;
    PyNs3AttributeValue *v13 = NULL;
    ns3::EmptyAttributeValue v13_default = ns3::EmptyAttributeValue();
    const char *n14 = NULL;
    Py_ssize_t n14_len;
    PyNs3AttributeValue *v14 = NULL;
    ns3::EmptyAttributeValue v14_default = ns3::EmptyAttributeValue();
    const char *n15 = NULL;
    Py_ssize_t n15_len;
    PyNs3AttributeValue *v15 = NULL;
    ns3::EmptyAttributeValue v15_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", "n09", "v09", "n10", "v10", "n11", "v11", "n12", "v12", "n13", "v13", "n14", "v14", "n15", "v15", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08, &n09, &n09_len, &PyNs3AttributeValue_Type, &v09, &n10, &n10_len, &PyNs3AttributeValue_Type, &v10, &n11, &n11_len, &PyNs3AttributeValue_Type, &v11, &n12, &n12_len, &PyNs3AttributeValue_Type, &v12, &n13, &n13_len, &PyNs3AttributeValue_Type, &v13, &n14, &n14_len, &PyNs3AttributeValue_Type, &v14, &n15, &n15_len, &PyNs3AttributeValue_Type, &v15)) {
        return NULL;
    }
    retval = self->obj->SetRootQueueDisc(std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default), (n09 ? std::string(n09, n09_len) : ""), (v09 ? (*((PyNs3AttributeValue *) v09)->obj) : v09_default), (n10 ? std::string(n10, n10_len) : ""), (v10 ? (*((PyNs3AttributeValue *) v10)->obj) : v10_default), (n11 ? std::string(n11, n11_len) : ""), (v11 ? (*((PyNs3AttributeValue *) v11)->obj) : v11_default), (n12 ? std::string(n12, n12_len) : ""), (v12 ? (*((PyNs3AttributeValue *) v12)->obj) : v12_default), (n13 ? std::string(n13, n13_len) : ""), (v13 ? (*((PyNs3AttributeValue *) v13)->obj) : v13_default), (n14 ? std::string(n14, n14_len) : ""), (v14 ? (*((PyNs3AttributeValue *) v14)->obj) : v14_default), (n15 ? std::string(n15, n15_len) : ""), (v15 ? (*((PyNs3AttributeValue *) v15)->obj) : v15_default));
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlHelper_AddChildQueueDisc(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    uint16_t retval;
    int handle;
    int classId;
    const char *type;
    Py_ssize_t type_len;
    const char *n01 = NULL;
    Py_ssize_t n01_len;
    PyNs3AttributeValue *v01 = NULL;
    ns3::EmptyAttributeValue v01_default = ns3::EmptyAttributeValue();
    const char *n02 = NULL;
    Py_ssize_t n02_len;
    PyNs3AttributeValue *v02 = NULL;
    ns3::EmptyAttributeValue v02_default = ns3::EmptyAttributeValue();
    const char *n03 = NULL;
    Py_ssize_t n03_len;
    PyNs3AttributeValue *v03 = NULL;
    ns3::EmptyAttributeValue v03_default = ns3::EmptyAttributeValue();
    const char *n04 = NULL;
    Py_ssize_t n04_len;
    PyNs3AttributeValue *v04 = NULL;
    ns3::EmptyAttributeValue v04_default = ns3::EmptyAttributeValue();
    const char *n05 = NULL;
    Py_ssize_t n05_len;
    PyNs3AttributeValue *v05 = NULL;
    ns3::EmptyAttributeValue v05_default = ns3::EmptyAttributeValue();
    const char *n06 = NULL;
    Py_ssize_t n06_len;
    PyNs3AttributeValue *v06 = NULL;
    ns3::EmptyAttributeValue v06_default = ns3::EmptyAttributeValue();
    const char *n07 = NULL;
    Py_ssize_t n07_len;
    PyNs3AttributeValue *v07 = NULL;
    ns3::EmptyAttributeValue v07_default = ns3::EmptyAttributeValue();
    const char *n08 = NULL;
    Py_ssize_t n08_len;
    PyNs3AttributeValue *v08 = NULL;
    ns3::EmptyAttributeValue v08_default = ns3::EmptyAttributeValue();
    const char *n09 = NULL;
    Py_ssize_t n09_len;
    PyNs3AttributeValue *v09 = NULL;
    ns3::EmptyAttributeValue v09_default = ns3::EmptyAttributeValue();
    const char *n10 = NULL;
    Py_ssize_t n10_len;
    PyNs3AttributeValue *v10 = NULL;
    ns3::EmptyAttributeValue v10_default = ns3::EmptyAttributeValue();
    const char *n11 = NULL;
    Py_ssize_t n11_len;
    PyNs3AttributeValue *v11 = NULL;
    ns3::EmptyAttributeValue v11_default = ns3::EmptyAttributeValue();
    const char *n12 = NULL;
    Py_ssize_t n12_len;
    PyNs3AttributeValue *v12 = NULL;
    ns3::EmptyAttributeValue v12_default = ns3::EmptyAttributeValue();
    const char *n13 = NULL;
    Py_ssize_t n13_len;
    PyNs3AttributeValue *v13 = NULL;
    ns3::EmptyAttributeValue v13_default = ns3::EmptyAttributeValue();
    const char *n14 = NULL;
    Py_ssize_t n14_len;
    PyNs3AttributeValue *v14 = NULL;
    ns3::EmptyAttributeValue v14_default = ns3::EmptyAttributeValue();
    const char *n15 = NULL;
    Py_ssize_t n15_len;
    PyNs3AttributeValue *v15 = NULL;
    ns3::EmptyAttributeValue v15_default = ns3::EmptyAttributeValue();
    const char *keywords[] = {"handle", "classId", "type", "n01", "v01", "n02", "v02", "n03", "v03", "n04", "v04", "n05", "v05", "n06", "v06", "n07", "v07", "n08", "v08", "n09", "v09", "n10", "v10", "n11", "v11", "n12", "v12", "n13", "v13", "n14", "v14", "n15", "v15", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iis#|s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!s#O!", (char **) keywords, &handle, &classId, &type, &type_len, &n01, &n01_len, &PyNs3AttributeValue_Type, &v01, &n02, &n02_len, &PyNs3AttributeValue_Type, &v02, &n03, &n03_len, &PyNs3AttributeValue_Type, &v03, &n04, &n04_len, &PyNs3AttributeValue_Type, &v04, &n05, &n05_len, &PyNs3AttributeValue_Type, &v05, &n06, &n06_len, &PyNs3AttributeValue_Type, &v06, &n07, &n07_len, &PyNs3AttributeValue_Type, &v07, &n08, &n08_len, &PyNs3AttributeValue_Type, &v08, &n09, &n09_len, &PyNs3AttributeValue_Type, &v09, &n10, &n10_len, &PyNs3AttributeValue_Type, &v10, &n11, &n11_len, &PyNs3AttributeValue_Type, &v11, &n12, &n12_len, &PyNs3AttributeValue_Type, &v12, &n13, &n13_len, &PyNs3AttributeValue_Type, &v13, &n14, &n14_len, &PyNs3AttributeValue_Type, &v14, &n15, &n15_len, &PyNs3AttributeValue_Type, &v15)) {
        return NULL;
    }
    if (handle > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    if (classId > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    retval = self->obj->AddChildQueueDisc(handle, classId, std::string(type, type_len), (n01 ? std::string(n01, n01_len) : ""), (v01 ? (*((PyNs3AttributeValue *) v01)->obj) : v01_default), (n02 ? std::string(n02, n02_len) : ""), (v02 ? (*((PyNs3AttributeValue *) v02)->obj) : v02_default), (n03 ? std::string(n03, n03_len) : ""), (v03 ? (*((PyNs3AttributeValue *) v03)->obj) : v03_default), (n04 ? std::string(n04, n04_len) : ""), (v04 ? (*((PyNs3AttributeValue *) v04)->obj) : v04_default), (n05 ? std::string(n05, n05_len) : ""), (v05 ? (*((PyNs3AttributeValue *) v05)->obj) : v05_default), (n06 ? std::string(n06, n06_len) : ""), (v06 ? (*((PyNs3AttributeValue *) v06)->obj) : v06_default), (n07 ? std::string(n07, n07_len) : ""), (v07 ? (*((PyNs3AttributeValue *) v07)->obj) : v07_default), (n08 ? std::string(n08, n08_len) : ""), (v08 ? (*((PyNs3AttributeValue *) v08)->obj) : v08_default), (n09 ? std::string(n09, n09_len) : ""), (v09 ? (*((PyNs3AttributeValue *) v09)->obj) : v09_default), (n10 ? std::string(n10, n10_len) : ""), (v10 ? (*((PyNs3AttributeValue *) v10)->obj) : v10_default), (n11 ? std::string(n11, n11_len) : ""), (v11 ? (*((PyNs3AttributeValue *) v11)->obj) : v11_default), (n12 ? std::string(n12, n12_len) : ""), (v12 ? (*((PyNs3AttributeValue *) v12)->obj) : v12_default), (n13 ? std::string(n13, n13_len) : ""), (v13 ? (*((PyNs3AttributeValue *) v13)->obj) : v13_default), (n14 ? std::string(n14, n14_len) : ""), (v14 ? (*((PyNs3AttributeValue *) v14)->obj) : v14_default), (n15 ? std::string(n15, n15_len) : ""), (v15 ? (*((PyNs3AttributeValue *) v15)->obj) : v15_default));
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}



PyObject *
_wrap_PyNs3TrafficControlHelper_Uninstall__0(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyObject *py_retval;
    PyNs3NetDeviceContainer *c;
    const char *keywords[] = {"c", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDeviceContainer_Type, &c)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }
    self->obj->Uninstall(*((PyNs3NetDeviceContainer *) c)->obj);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
_wrap_PyNs3TrafficControlHelper_Uninstall__1(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyObject *py_retval;
    PyNs3NetDevice *d;
    ns3::NetDevice *d_ptr;
    const char *keywords[] = {"d", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDevice_Type, &d)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }
    d_ptr = (d ? d->obj : NULL);
    self->obj->Uninstall(ns3::Ptr< ns3::NetDevice  > (d_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject * _wrap_PyNs3TrafficControlHelper_Uninstall(PyNs3TrafficControlHelper *self, PyObject *args, PyObject *kwargs)
{
    PyObject * retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3TrafficControlHelper_Uninstall__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3TrafficControlHelper_Uninstall__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return NULL;
}


static PyObject*
_wrap_PyNs3TrafficControlHelper__copy__(PyNs3TrafficControlHelper *self)
{

    PyNs3TrafficControlHelper *py_copy;
    py_copy = PyObject_New(PyNs3TrafficControlHelper, &PyNs3TrafficControlHelper_Type);
    py_copy->obj = new ns3::TrafficControlHelper(*self->obj);
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3TrafficControlHelper_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3TrafficControlHelper_methods[] = {
    {(char *) "AddChildQueueDiscs", (PyCFunction) _wrap_PyNs3TrafficControlHelper_AddChildQueueDiscs, METH_KEYWORDS|METH_VARARGS, "AddChildQueueDiscs(handle, classes, type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08, n09, v09, n10, v10, n11, v11, n12, v12, n13, v13, n14, v14, n15, v15)\n\ntype: handle: uint16_t\ntype: classes: std::vector< short unsigned int > const &\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &\ntype: n09: std::string\ntype: v09: ns3::AttributeValue const &\ntype: n10: std::string\ntype: v10: ns3::AttributeValue const &\ntype: n11: std::string\ntype: v11: ns3::AttributeValue const &\ntype: n12: std::string\ntype: v12: ns3::AttributeValue const &\ntype: n13: std::string\ntype: v13: ns3::AttributeValue const &\ntype: n14: std::string\ntype: v14: ns3::AttributeValue const &\ntype: n15: std::string\ntype: v15: ns3::AttributeValue const &" },
    {(char *) "AddInternalQueues", (PyCFunction) _wrap_PyNs3TrafficControlHelper_AddInternalQueues, METH_KEYWORDS|METH_VARARGS, "AddInternalQueues(handle, count, type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08)\n\ntype: handle: uint16_t\ntype: count: uint16_t\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &" },
    {(char *) "Default", (PyCFunction) _wrap_PyNs3TrafficControlHelper_Default, METH_NOARGS|METH_STATIC, "Default()\n\n" },
    {(char *) "AddQueueDiscClasses", (PyCFunction) _wrap_PyNs3TrafficControlHelper_AddQueueDiscClasses, METH_KEYWORDS|METH_VARARGS, "AddQueueDiscClasses(handle, count, type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08)\n\ntype: handle: uint16_t\ntype: count: uint16_t\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &" },
    {(char *) "AddPacketFilter", (PyCFunction) _wrap_PyNs3TrafficControlHelper_AddPacketFilter, METH_KEYWORDS|METH_VARARGS, "AddPacketFilter(handle, type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08)\n\ntype: handle: uint16_t\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &" },
    {(char *) "Install", (PyCFunction) _wrap_PyNs3TrafficControlHelper_Install, METH_KEYWORDS|METH_VARARGS, NULL },
    {(char *) "SetQueueLimits", (PyCFunction) _wrap_PyNs3TrafficControlHelper_SetQueueLimits, METH_KEYWORDS|METH_VARARGS, "SetQueueLimits(type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08)\n\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &" },
    {(char *) "SetRootQueueDisc", (PyCFunction) _wrap_PyNs3TrafficControlHelper_SetRootQueueDisc, METH_KEYWORDS|METH_VARARGS, "SetRootQueueDisc(type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08, n09, v09, n10, v10, n11, v11, n12, v12, n13, v13, n14, v14, n15, v15)\n\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &\ntype: n09: std::string\ntype: v09: ns3::AttributeValue const &\ntype: n10: std::string\ntype: v10: ns3::AttributeValue const &\ntype: n11: std::string\ntype: v11: ns3::AttributeValue const &\ntype: n12: std::string\ntype: v12: ns3::AttributeValue const &\ntype: n13: std::string\ntype: v13: ns3::AttributeValue const &\ntype: n14: std::string\ntype: v14: ns3::AttributeValue const &\ntype: n15: std::string\ntype: v15: ns3::AttributeValue const &" },
    {(char *) "AddChildQueueDisc", (PyCFunction) _wrap_PyNs3TrafficControlHelper_AddChildQueueDisc, METH_KEYWORDS|METH_VARARGS, "AddChildQueueDisc(handle, classId, type, n01, v01, n02, v02, n03, v03, n04, v04, n05, v05, n06, v06, n07, v07, n08, v08, n09, v09, n10, v10, n11, v11, n12, v12, n13, v13, n14, v14, n15, v15)\n\ntype: handle: uint16_t\ntype: classId: uint16_t\ntype: type: std::string\ntype: n01: std::string\ntype: v01: ns3::AttributeValue const &\ntype: n02: std::string\ntype: v02: ns3::AttributeValue const &\ntype: n03: std::string\ntype: v03: ns3::AttributeValue const &\ntype: n04: std::string\ntype: v04: ns3::AttributeValue const &\ntype: n05: std::string\ntype: v05: ns3::AttributeValue const &\ntype: n06: std::string\ntype: v06: ns3::AttributeValue const &\ntype: n07: std::string\ntype: v07: ns3::AttributeValue const &\ntype: n08: std::string\ntype: v08: ns3::AttributeValue const &\ntype: n09: std::string\ntype: v09: ns3::AttributeValue const &\ntype: n10: std::string\ntype: v10: ns3::AttributeValue const &\ntype: n11: std::string\ntype: v11: ns3::AttributeValue const &\ntype: n12: std::string\ntype: v12: ns3::AttributeValue const &\ntype: n13: std::string\ntype: v13: ns3::AttributeValue const &\ntype: n14: std::string\ntype: v14: ns3::AttributeValue const &\ntype: n15: std::string\ntype: v15: ns3::AttributeValue const &" },
    {(char *) "Uninstall", (PyCFunction) _wrap_PyNs3TrafficControlHelper_Uninstall, METH_KEYWORDS|METH_VARARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3TrafficControlHelper__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
_wrap_PyNs3TrafficControlHelper__tp_dealloc(PyNs3TrafficControlHelper *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3TrafficControlHelper_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3TrafficControlHelper_wrapper_registry.end()) {
        PyNs3TrafficControlHelper_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
        ns3::TrafficControlHelper *tmp = self->obj;
        self->obj = NULL;
        if (!(self->flags&PYBINDGEN_WRAPPER_FLAG_OBJECT_NOT_OWNED)) {
            delete tmp;
        }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3TrafficControlHelper__tp_richcompare (PyNs3TrafficControlHelper *PYBINDGEN_UNUSED(self), PyNs3TrafficControlHelper *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3TrafficControlHelper_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3TrafficControlHelper_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.TrafficControlHelper",            /* tp_name */
    sizeof(PyNs3TrafficControlHelper),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3TrafficControlHelper__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    "TrafficControlHelper(arg0)\nTrafficControlHelper()",                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3TrafficControlHelper__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3TrafficControlHelper_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3TrafficControlHelper__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3PacketFilter__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3PacketFilter *self)
{
    PyObject *py_retval;
    PyNs3PacketFilter__PythonHelper *helper = dynamic_cast< PyNs3PacketFilter__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PacketFilter__PythonHelper::_wrap_DoInitialize(PyNs3PacketFilter *self)
{
    PyObject *py_retval;
    PyNs3PacketFilter__PythonHelper *helper = dynamic_cast< PyNs3PacketFilter__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PacketFilter__PythonHelper::_wrap_NotifyNewAggregate(PyNs3PacketFilter *self)
{
    PyObject *py_retval;
    PyNs3PacketFilter__PythonHelper *helper = dynamic_cast< PyNs3PacketFilter__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PacketFilter__PythonHelper::_wrap_DoDispose(PyNs3PacketFilter *self)
{
    PyObject *py_retval;
    PyNs3PacketFilter__PythonHelper *helper = dynamic_cast< PyNs3PacketFilter__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

bool
PyNs3PacketFilter__PythonHelper::CheckProtocol(ns3::Ptr< ns3::QueueDiscItem > item) const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PacketFilter *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckProtocol"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = const_cast< ns3::PacketFilter* >((const ns3::PacketFilter*) this);
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckProtocol", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

int32_t
PyNs3PacketFilter__PythonHelper::DoClassify(ns3::Ptr< ns3::QueueDiscItem > item) const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PacketFilter *self_obj_before;
    PyObject *py_retval;
    int32_t retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoClassify"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = const_cast< ns3::PacketFilter* >((const ns3::PacketFilter*) this);
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoClassify", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "i", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PacketFilter* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::TypeId
PyNs3PacketFilter__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PacketFilter__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3PacketFilter__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3PacketFilter__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3PacketFilter__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}
static PyObject* _wrap_PyNs3PacketFilter__get_PF_NO_MATCH(PyObject * PYBINDGEN_UNUSED(obj), void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "i", ns3::PacketFilter::PF_NO_MATCH);
    return py_retval;
}
static PyGetSetDef Ns3PacketFilterMeta__getsets[] = {
    {
        (char*) "PF_NO_MATCH", /* attribute name */
        (getter) _wrap_PyNs3PacketFilter__get_PF_NO_MATCH, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject PyNs3PacketFilterMeta_Type = {
        PyVarObject_HEAD_INIT(NULL, 0)
	(char *) "Ns3PacketFilterMeta",		        /* tp_name */
	0,					/* tp_basicsize */
	0,					/* tp_itemsize */
	0,	 				/* tp_dealloc */
	0,					/* tp_print */
	0,					/* tp_getattr */
	0,					/* tp_setattr */
	0,					/* tp_compare */
	0,					/* tp_repr */
	0,					/* tp_as_number */
	0,					/* tp_as_sequence */
	0,		       			/* tp_as_mapping */
	0,					/* tp_hash */
	0,					/* tp_call */
	0,					/* tp_str */
	0,					/* tp_getattro */
	0,					/* tp_setattro */
	0,					/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC|Py_TPFLAGS_BASETYPE, /* tp_flags */
 	0,					/* tp_doc */
	0,					/* tp_traverse */
 	0,					/* tp_clear */
	0,					/* tp_richcompare */
	0,					/* tp_weaklistoffset */
	0,					/* tp_iter */
	0,					/* tp_iternext */
	0,					/* tp_methods */
	0,					/* tp_members */
	Ns3PacketFilterMeta__getsets,				/* tp_getset */
	0,					/* tp_base */
	0,					/* tp_dict */
	0,	                                /* tp_descr_get */
	0,  		                        /* tp_descr_set */
	0,					/* tp_dictoffset */
	0,					/* tp_init */
	0,					/* tp_alloc */
	0,					/* tp_new */
	0,               			/* tp_free */
        0,                                      /* tp_is_gc */
        0,                                      /* tp_bases */
        0,                                      /* tp_mro */
        0,                                      /* tp_cache */
        0,                                      /* tp_subclasses */
        0,                                      /* tp_weaklist */
        0                                       /* tp_del */
};



static int
_wrap_PyNs3PacketFilter__tp_init__0(PyNs3PacketFilter *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3PacketFilter *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3PacketFilter_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3PacketFilter_Type)
    {
        self->obj = new PyNs3PacketFilter__PythonHelper(*((PyNs3PacketFilter *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3PacketFilter__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        PyErr_SetString(PyExc_TypeError, "class 'PacketFilter' cannot be constructed");
        return -1;
    }
    return 0;
}

static int
_wrap_PyNs3PacketFilter__tp_init__1(PyNs3PacketFilter *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3PacketFilter_Type)
    {
        self->obj = new PyNs3PacketFilter__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3PacketFilter__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        PyErr_SetString(PyExc_TypeError, "class 'PacketFilter' cannot be constructed");
        return -1;
    }
    return 0;
}

int _wrap_PyNs3PacketFilter__tp_init(PyNs3PacketFilter *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3PacketFilter__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3PacketFilter__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3PacketFilter_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::PacketFilter::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3PacketFilter_Classify(PyNs3PacketFilter *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int32_t retval;
    PyNs3QueueDiscItem *item;
    ns3::QueueDiscItem *item_ptr;
    const char *keywords[] = {"item", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscItem_Type, &item)) {
        return NULL;
    }
    item_ptr = (item ? item->obj : NULL);
    retval = self->obj->Classify(ns3::Ptr< ns3::QueueDiscItem  > (item_ptr));
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}

static PyMethodDef PyNs3PacketFilter_methods[] = {
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3PacketFilter_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "Classify", (PyCFunction) _wrap_PyNs3PacketFilter_Classify, METH_KEYWORDS|METH_VARARGS, "Classify(item)\n\ntype: item: ns3::Ptr< ns3::QueueDiscItem >" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3PacketFilter__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3PacketFilter__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3PacketFilter__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3PacketFilter__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {NULL, NULL, 0, NULL}
};

static void
PyNs3PacketFilter__tp_clear(PyNs3PacketFilter *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::PacketFilter *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3PacketFilter__tp_traverse(PyNs3PacketFilter *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3PacketFilter__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3PacketFilter__tp_dealloc(PyNs3PacketFilter *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3PacketFilter__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3PacketFilter__tp_richcompare (PyNs3PacketFilter *PYBINDGEN_UNUSED(self), PyNs3PacketFilter *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3PacketFilter_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3PacketFilter_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.PacketFilter",            /* tp_name */
    sizeof(PyNs3PacketFilter),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3PacketFilter__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "PacketFilter(arg0)\nPacketFilter()",                        /* Documentation string */
    (traverseproc)PyNs3PacketFilter__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3PacketFilter__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3PacketFilter__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3PacketFilter_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3PacketFilter, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3PacketFilter__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3QueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    PyNs3QueueDisc__PythonHelper *helper = dynamic_cast< PyNs3QueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDisc__PythonHelper::_wrap_DoInitialize(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    PyNs3QueueDisc__PythonHelper *helper = dynamic_cast< PyNs3QueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDisc__PythonHelper::_wrap_NotifyNewAggregate(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    PyNs3QueueDisc__PythonHelper *helper = dynamic_cast< PyNs3QueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDisc__PythonHelper::_wrap_Drop(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3QueueItem *item;
    ns3::QueueItem *item_ptr;
    PyNs3QueueDisc__PythonHelper *helper = dynamic_cast< PyNs3QueueDisc__PythonHelper* >(self->obj);
    const char *keywords[] = {"item", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueItem_Type, &item)) {
        return NULL;
    }
    item_ptr = (item ? item->obj : NULL);
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method Drop of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->Drop__parent_caller(ns3::Ptr< ns3::QueueItem  > (item_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDisc__PythonHelper::_wrap_DoDispose(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    PyNs3QueueDisc__PythonHelper *helper = dynamic_cast< PyNs3QueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

uint32_t
PyNs3QueueDisc__PythonHelper::GetQuota() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    uint32_t retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetQuota", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}


void
PyNs3QueueDisc__PythonHelper::SetQuota(uint32_t const quota)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::SetQuota(quota);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetQuota", (char *) "N", PyLong_FromUnsignedLong(quota));
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3QueueDisc__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3QueueDisc__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

bool
PyNs3QueueDisc__PythonHelper::CheckConfig()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckConfig"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckConfig", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem >
PyNs3QueueDisc__PythonHelper::DoDequeue()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDequeue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDequeue", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

bool
PyNs3QueueDisc__PythonHelper::DoEnqueue(ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoEnqueue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoEnqueue", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem const >
PyNs3QueueDisc__PythonHelper::DoPeek() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoPeek"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoPeek", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3QueueDisc__PythonHelper::InitializeParams()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "InitializeParams"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "InitializeParams", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3QueueDisc__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3QueueDisc__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3QueueDisc__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3QueueDisc__tp_init__0(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3QueueDisc *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDisc_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3QueueDisc_Type)
    {
        self->obj = new PyNs3QueueDisc__PythonHelper(*((PyNs3QueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3QueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        PyErr_SetString(PyExc_TypeError, "class 'QueueDisc' cannot be constructed");
        return -1;
    }
    return 0;
}

static int
_wrap_PyNs3QueueDisc__tp_init__1(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3QueueDisc_Type)
    {
        self->obj = new PyNs3QueueDisc__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3QueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        PyErr_SetString(PyExc_TypeError, "class 'QueueDisc' cannot be constructed");
        return -1;
    }
    return 0;
}

int _wrap_PyNs3QueueDisc__tp_init(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3QueueDisc__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3QueueDisc__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTotalReceivedBytes(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetTotalReceivedBytes();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetQuota(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    PyNs3QueueDisc__PythonHelper *helper_class = dynamic_cast<PyNs3QueueDisc__PythonHelper*> (self->obj);
    
    retval = (helper_class == NULL)? (self->obj->GetQuota()) : (self->obj->ns3::QueueDisc::GetQuota());
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::QueueDisc::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTotalDroppedBytes(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetTotalDroppedBytes();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetNPackets(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetNPackets();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_AddQueueDiscClass(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3QueueDiscClass *qdClass;
    ns3::QueueDiscClass *qdClass_ptr;
    const char *keywords[] = {"qdClass", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscClass_Type, &qdClass)) {
        return NULL;
    }
    qdClass_ptr = (qdClass ? qdClass->obj : NULL);
    self->obj->AddQueueDiscClass(ns3::Ptr< ns3::QueueDiscClass  > (qdClass_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetNInternalQueues(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetNInternalQueues();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetNPacketFilters(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetNPacketFilters();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTotalRequeuedBytes(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetTotalRequeuedBytes();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_Peek(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    retval = self->obj->Peek();
    if (!(const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL) {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval)))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDiscItem);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_Run(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    
    self->obj->Run();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetPacketFilter(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::PacketFilter > retval;
    unsigned int i;
    const char *keywords[] = {"i", NULL};
    PyNs3PacketFilter *py_PacketFilter;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &i)) {
        return NULL;
    }
    retval = self->obj->GetPacketFilter(i);
    if (!(const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3PacketFilter__PythonHelper).name())
    {
        py_PacketFilter = reinterpret_cast< PyNs3PacketFilter* >(reinterpret_cast< PyNs3PacketFilter__PythonHelper* >(const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval)))->m_pyself);
        py_PacketFilter->obj = const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval));
        Py_INCREF(py_PacketFilter);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_PacketFilter = NULL;
        } else {
            py_PacketFilter = (PyNs3PacketFilter *) wrapper_lookup_iter->second;
            Py_INCREF(py_PacketFilter);
        }
    
        if (py_PacketFilter == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval)))), &PyNs3PacketFilter_Type);
            py_PacketFilter = PyObject_GC_New(PyNs3PacketFilter, wrapper_type);
            py_PacketFilter->inst_dict = NULL;
    
            py_PacketFilter->inst_dict = NULL;
            py_PacketFilter->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval))->Ref();
            py_PacketFilter->obj = const_cast<ns3::PacketFilter *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_PacketFilter->obj] = (PyObject *) py_PacketFilter;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_PacketFilter);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetNQueueDiscClasses(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetNQueueDiscClasses();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_Enqueue(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *item;
    ns3::QueueDiscItem *item_ptr;
    const char *keywords[] = {"item", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscItem_Type, &item)) {
        return NULL;
    }
    item_ptr = (item ? item->obj : NULL);
    retval = self->obj->Enqueue(ns3::Ptr< ns3::QueueDiscItem  > (item_ptr));
    py_retval = Py_BuildValue((char *) "N", PyBool_FromLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_Classify(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int32_t retval;
    PyNs3QueueDiscItem *item;
    ns3::QueueDiscItem *item_ptr;
    const char *keywords[] = {"item", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscItem_Type, &item)) {
        return NULL;
    }
    item_ptr = (item ? item->obj : NULL);
    retval = self->obj->Classify(ns3::Ptr< ns3::QueueDiscItem  > (item_ptr));
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetInternalQueue(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::Queue > retval;
    unsigned int i;
    const char *keywords[] = {"i", NULL};
    PyNs3Queue *py_Queue;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &i)) {
        return NULL;
    }
    retval = self->obj->GetInternalQueue(i);
    if (!(const_cast<ns3::Queue *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::Queue *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3Queue__PythonHelper).name())
    {
        py_Queue = reinterpret_cast< PyNs3Queue* >(reinterpret_cast< PyNs3Queue__PythonHelper* >(const_cast<ns3::Queue *> (ns3::PeekPointer (retval)))->m_pyself);
        py_Queue->obj = const_cast<ns3::Queue *> (ns3::PeekPointer (retval));
        Py_INCREF(py_Queue);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::Queue *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_Queue = NULL;
        } else {
            py_Queue = (PyNs3Queue *) wrapper_lookup_iter->second;
            Py_INCREF(py_Queue);
        }
    
        if (py_Queue == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::Queue *> (ns3::PeekPointer (retval)))), &PyNs3Queue_Type);
            py_Queue = PyObject_GC_New(PyNs3Queue, wrapper_type);
            py_Queue->inst_dict = NULL;
    
            py_Queue->inst_dict = NULL;
            py_Queue->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::Queue *> (ns3::PeekPointer (retval))->Ref();
            py_Queue->obj = const_cast<ns3::Queue *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_Queue->obj] = (PyObject *) py_Queue;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_Queue);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTotalReceivedPackets(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetTotalReceivedPackets();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetWakeMode(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    ns3::QueueDisc::WakeMode retval;
    
    retval = self->obj->GetWakeMode();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_SetQuota(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    unsigned int quota;
    PyNs3QueueDisc__PythonHelper *helper_class = dynamic_cast<PyNs3QueueDisc__PythonHelper*> (self->obj);
    const char *keywords[] = {"quota", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &quota)) {
        return NULL;
    }
    (helper_class == NULL)? (self->obj->SetQuota(quota)) : (self->obj->ns3::QueueDisc::SetQuota(quota));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTotalDroppedPackets(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetTotalDroppedPackets();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_SetNetDevice(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    const char *keywords[] = {"device", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDevice_Type, &device)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    self->obj->SetNetDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_SetParentDropCallback(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyObject *cb;
    ns3::Ptr<PythonCallbackImpl2> cb_cb_impl;
    PyNs3QueueDisc__PythonHelper *helper_class = dynamic_cast<PyNs3QueueDisc__PythonHelper*> (self->obj);
    const char *keywords[] = {"cb", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O", (char **) keywords, &cb)) {
        return NULL;
    }
    if (!PyCallable_Check(cb)) {
        PyErr_SetString(PyExc_TypeError, "parameter 'cb' must be callbale");
        return NULL;
    }
    cb_cb_impl = ns3::Create<PythonCallbackImpl2> (cb);
    (helper_class == NULL)? (self->obj->SetParentDropCallback(ns3::Callback<void, ns3::Ptr<ns3::QueueItem>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> (cb_cb_impl))) : (self->obj->ns3::QueueDisc::SetParentDropCallback(ns3::Callback<void, ns3::Ptr<ns3::QueueItem>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> (cb_cb_impl)));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetNetDevice(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::NetDevice > retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    retval = self->obj->GetNetDevice();
    if (!(const_cast<ns3::NetDevice *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (retval)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL) {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::NetDevice *> (ns3::PeekPointer (retval)))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->inst_dict = NULL;
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (retval))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (retval));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    py_retval = Py_BuildValue((char *) "N", py_NetDevice);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_AddInternalQueue(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3Queue *queue;
    ns3::Queue *queue_ptr;
    const char *keywords[] = {"queue", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3Queue_Type, &queue)) {
        return NULL;
    }
    queue_ptr = (queue ? queue->obj : NULL);
    self->obj->AddInternalQueue(ns3::Ptr< ns3::Queue  > (queue_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_Dequeue(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    retval = self->obj->Dequeue();
    if (!(const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL) {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval)))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (retval));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDiscItem);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_AddPacketFilter(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3PacketFilter *filter;
    ns3::PacketFilter *filter_ptr;
    const char *keywords[] = {"filter", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3PacketFilter_Type, &filter)) {
        return NULL;
    }
    filter_ptr = (filter ? filter->obj : NULL);
    self->obj->AddPacketFilter(ns3::Ptr< ns3::PacketFilter  > (filter_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetTotalRequeuedPackets(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetTotalRequeuedPackets();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetNBytes(PyNs3QueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetNBytes();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDisc_GetQueueDiscClass(PyNs3QueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscClass > retval;
    unsigned int i;
    const char *keywords[] = {"i", NULL};
    PyNs3QueueDiscClass *py_QueueDiscClass;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &i)) {
        return NULL;
    }
    retval = self->obj->GetQueueDiscClass(i);
    if (!(const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3QueueDiscClass__PythonHelper).name())
    {
        py_QueueDiscClass = reinterpret_cast< PyNs3QueueDiscClass* >(reinterpret_cast< PyNs3QueueDiscClass__PythonHelper* >(const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval)))->m_pyself);
        py_QueueDiscClass->obj = const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval));
        Py_INCREF(py_QueueDiscClass);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDiscClass = NULL;
        } else {
            py_QueueDiscClass = (PyNs3QueueDiscClass *) wrapper_lookup_iter->second;
            Py_INCREF(py_QueueDiscClass);
        }
    
        if (py_QueueDiscClass == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval)))), &PyNs3QueueDiscClass_Type);
            py_QueueDiscClass = PyObject_GC_New(PyNs3QueueDiscClass, wrapper_type);
            py_QueueDiscClass->inst_dict = NULL;
    
            py_QueueDiscClass->inst_dict = NULL;
            py_QueueDiscClass->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval))->Ref();
            py_QueueDiscClass->obj = const_cast<ns3::QueueDiscClass *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDiscClass->obj] = (PyObject *) py_QueueDiscClass;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDiscClass);
    return py_retval;
}

static PyMethodDef PyNs3QueueDisc_methods[] = {
    {(char *) "GetTotalReceivedBytes", (PyCFunction) _wrap_PyNs3QueueDisc_GetTotalReceivedBytes, METH_NOARGS, "GetTotalReceivedBytes()\n\n" },
    {(char *) "GetQuota", (PyCFunction) _wrap_PyNs3QueueDisc_GetQuota, METH_NOARGS, "GetQuota()\n\n" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3QueueDisc_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "GetTotalDroppedBytes", (PyCFunction) _wrap_PyNs3QueueDisc_GetTotalDroppedBytes, METH_NOARGS, "GetTotalDroppedBytes()\n\n" },
    {(char *) "GetNPackets", (PyCFunction) _wrap_PyNs3QueueDisc_GetNPackets, METH_NOARGS, "GetNPackets()\n\n" },
    {(char *) "AddQueueDiscClass", (PyCFunction) _wrap_PyNs3QueueDisc_AddQueueDiscClass, METH_KEYWORDS|METH_VARARGS, "AddQueueDiscClass(qdClass)\n\ntype: qdClass: ns3::Ptr< ns3::QueueDiscClass >" },
    {(char *) "GetNInternalQueues", (PyCFunction) _wrap_PyNs3QueueDisc_GetNInternalQueues, METH_NOARGS, "GetNInternalQueues()\n\n" },
    {(char *) "GetNPacketFilters", (PyCFunction) _wrap_PyNs3QueueDisc_GetNPacketFilters, METH_NOARGS, "GetNPacketFilters()\n\n" },
    {(char *) "GetTotalRequeuedBytes", (PyCFunction) _wrap_PyNs3QueueDisc_GetTotalRequeuedBytes, METH_NOARGS, "GetTotalRequeuedBytes()\n\n" },
    {(char *) "Peek", (PyCFunction) _wrap_PyNs3QueueDisc_Peek, METH_NOARGS, "Peek()\n\n" },
    {(char *) "Run", (PyCFunction) _wrap_PyNs3QueueDisc_Run, METH_NOARGS, "Run()\n\n" },
    {(char *) "GetPacketFilter", (PyCFunction) _wrap_PyNs3QueueDisc_GetPacketFilter, METH_KEYWORDS|METH_VARARGS, "GetPacketFilter(i)\n\ntype: i: uint32_t" },
    {(char *) "GetNQueueDiscClasses", (PyCFunction) _wrap_PyNs3QueueDisc_GetNQueueDiscClasses, METH_NOARGS, "GetNQueueDiscClasses()\n\n" },
    {(char *) "Enqueue", (PyCFunction) _wrap_PyNs3QueueDisc_Enqueue, METH_KEYWORDS|METH_VARARGS, "Enqueue(item)\n\ntype: item: ns3::Ptr< ns3::QueueDiscItem >" },
    {(char *) "Classify", (PyCFunction) _wrap_PyNs3QueueDisc_Classify, METH_KEYWORDS|METH_VARARGS, "Classify(item)\n\ntype: item: ns3::Ptr< ns3::QueueDiscItem >" },
    {(char *) "GetInternalQueue", (PyCFunction) _wrap_PyNs3QueueDisc_GetInternalQueue, METH_KEYWORDS|METH_VARARGS, "GetInternalQueue(i)\n\ntype: i: uint32_t" },
    {(char *) "GetTotalReceivedPackets", (PyCFunction) _wrap_PyNs3QueueDisc_GetTotalReceivedPackets, METH_NOARGS, "GetTotalReceivedPackets()\n\n" },
    {(char *) "GetWakeMode", (PyCFunction) _wrap_PyNs3QueueDisc_GetWakeMode, METH_NOARGS, "GetWakeMode()\n\n" },
    {(char *) "SetQuota", (PyCFunction) _wrap_PyNs3QueueDisc_SetQuota, METH_KEYWORDS|METH_VARARGS, "SetQuota(quota)\n\ntype: quota: uint32_t const" },
    {(char *) "GetTotalDroppedPackets", (PyCFunction) _wrap_PyNs3QueueDisc_GetTotalDroppedPackets, METH_NOARGS, "GetTotalDroppedPackets()\n\n" },
    {(char *) "SetNetDevice", (PyCFunction) _wrap_PyNs3QueueDisc_SetNetDevice, METH_KEYWORDS|METH_VARARGS, "SetNetDevice(device)\n\ntype: device: ns3::Ptr< ns3::NetDevice >" },
    {(char *) "SetParentDropCallback", (PyCFunction) _wrap_PyNs3QueueDisc_SetParentDropCallback, METH_KEYWORDS|METH_VARARGS, "SetParentDropCallback(cb)\n\ntype: cb: ns3::Callback< void, ns3::Ptr< ns3::QueueItem >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >" },
    {(char *) "GetNetDevice", (PyCFunction) _wrap_PyNs3QueueDisc_GetNetDevice, METH_NOARGS, "GetNetDevice()\n\n" },
    {(char *) "AddInternalQueue", (PyCFunction) _wrap_PyNs3QueueDisc_AddInternalQueue, METH_KEYWORDS|METH_VARARGS, "AddInternalQueue(queue)\n\ntype: queue: ns3::Ptr< ns3::Queue >" },
    {(char *) "Dequeue", (PyCFunction) _wrap_PyNs3QueueDisc_Dequeue, METH_NOARGS, "Dequeue()\n\n" },
    {(char *) "AddPacketFilter", (PyCFunction) _wrap_PyNs3QueueDisc_AddPacketFilter, METH_KEYWORDS|METH_VARARGS, "AddPacketFilter(filter)\n\ntype: filter: ns3::Ptr< ns3::PacketFilter >" },
    {(char *) "GetTotalRequeuedPackets", (PyCFunction) _wrap_PyNs3QueueDisc_GetTotalRequeuedPackets, METH_NOARGS, "GetTotalRequeuedPackets()\n\n" },
    {(char *) "GetNBytes", (PyCFunction) _wrap_PyNs3QueueDisc_GetNBytes, METH_NOARGS, "GetNBytes()\n\n" },
    {(char *) "GetQueueDiscClass", (PyCFunction) _wrap_PyNs3QueueDisc_GetQueueDiscClass, METH_KEYWORDS|METH_VARARGS, "GetQueueDiscClass(i)\n\ntype: i: uint32_t" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3QueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3QueueDisc__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3QueueDisc__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "Drop", (PyCFunction) PyNs3QueueDisc__PythonHelper::_wrap_Drop, METH_KEYWORDS|METH_VARARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3QueueDisc__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {NULL, NULL, 0, NULL}
};

static void
PyNs3QueueDisc__tp_clear(PyNs3QueueDisc *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::QueueDisc *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3QueueDisc__tp_traverse(PyNs3QueueDisc *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3QueueDisc__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3QueueDisc__tp_dealloc(PyNs3QueueDisc *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3QueueDisc__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3QueueDisc__tp_richcompare (PyNs3QueueDisc *PYBINDGEN_UNUSED(self), PyNs3QueueDisc *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3QueueDisc_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3QueueDisc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.QueueDisc",            /* tp_name */
    sizeof(PyNs3QueueDisc),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3QueueDisc__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "QueueDisc(arg0)\nQueueDisc()",                        /* Documentation string */
    (traverseproc)PyNs3QueueDisc__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3QueueDisc__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3QueueDisc__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3QueueDisc_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3QueueDisc, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3QueueDisc__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3QueueDiscClass__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3QueueDiscClass *self)
{
    PyObject *py_retval;
    PyNs3QueueDiscClass__PythonHelper *helper = dynamic_cast< PyNs3QueueDiscClass__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDiscClass__PythonHelper::_wrap_DoInitialize(PyNs3QueueDiscClass *self)
{
    PyObject *py_retval;
    PyNs3QueueDiscClass__PythonHelper *helper = dynamic_cast< PyNs3QueueDiscClass__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDiscClass__PythonHelper::_wrap_NotifyNewAggregate(PyNs3QueueDiscClass *self)
{
    PyObject *py_retval;
    PyNs3QueueDiscClass__PythonHelper *helper = dynamic_cast< PyNs3QueueDiscClass__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3QueueDiscClass__PythonHelper::_wrap_DoDispose(PyNs3QueueDiscClass *self)
{
    PyObject *py_retval;
    PyNs3QueueDiscClass__PythonHelper *helper = dynamic_cast< PyNs3QueueDiscClass__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class QueueDiscClass is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

void
PyNs3QueueDiscClass__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDiscClass *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDiscClass::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDiscClass* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDiscClass* >(m_pyself)->obj = (ns3::QueueDiscClass*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDiscClass* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDiscClass* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDiscClass* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3QueueDiscClass__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3QueueDiscClass__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3QueueDiscClass__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3QueueDiscClass__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3QueueDiscClass__tp_init__0(PyNs3QueueDiscClass *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3QueueDiscClass *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDiscClass_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3QueueDiscClass_Type)
    {
        self->obj = new PyNs3QueueDiscClass__PythonHelper(*((PyNs3QueueDiscClass *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3QueueDiscClass__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::QueueDiscClass(*((PyNs3QueueDiscClass *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

static int
_wrap_PyNs3QueueDiscClass__tp_init__1(PyNs3QueueDiscClass *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3QueueDiscClass_Type)
    {
        self->obj = new PyNs3QueueDiscClass__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3QueueDiscClass__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::QueueDiscClass();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

int _wrap_PyNs3QueueDiscClass__tp_init(PyNs3QueueDiscClass *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3QueueDiscClass__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3QueueDiscClass__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3QueueDiscClass_GetQueueDisc(PyNs3QueueDiscClass *self)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDisc > retval;
    PyNs3QueueDisc *py_QueueDisc;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    retval = self->obj->GetQueueDisc();
    if (!(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3QueueDisc__PythonHelper).name())
    {
        py_QueueDisc = reinterpret_cast< PyNs3QueueDisc* >(reinterpret_cast< PyNs3QueueDisc__PythonHelper* >(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))->m_pyself);
        py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
        Py_INCREF(py_QueueDisc);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDisc = NULL;
        } else {
            py_QueueDisc = (PyNs3QueueDisc *) wrapper_lookup_iter->second;
            Py_INCREF(py_QueueDisc);
        }
    
        if (py_QueueDisc == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))), &PyNs3QueueDisc_Type);
            py_QueueDisc = PyObject_GC_New(PyNs3QueueDisc, wrapper_type);
            py_QueueDisc->inst_dict = NULL;
    
            py_QueueDisc->inst_dict = NULL;
            py_QueueDisc->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval))->Ref();
            py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDisc->obj] = (PyObject *) py_QueueDisc;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDisc);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscClass_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::QueueDiscClass::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscClass_SetQueueDisc(PyNs3QueueDiscClass *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3QueueDisc *qd;
    ns3::QueueDisc *qd_ptr;
    const char *keywords[] = {"qd", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3QueueDisc_Type, &qd)) {
        return NULL;
    }
    qd_ptr = (qd ? qd->obj : NULL);
    self->obj->SetQueueDisc(ns3::Ptr< ns3::QueueDisc  > (qd_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


static PyObject*
_wrap_PyNs3QueueDiscClass__copy__(PyNs3QueueDiscClass *self)
{

    PyNs3QueueDiscClass *py_copy;
    py_copy = PyObject_GC_New(PyNs3QueueDiscClass, &PyNs3QueueDiscClass_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::QueueDiscClass(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3QueueDiscClass_methods[] = {
    {(char *) "GetQueueDisc", (PyCFunction) _wrap_PyNs3QueueDiscClass_GetQueueDisc, METH_NOARGS, "GetQueueDisc()\n\n" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3QueueDiscClass_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "SetQueueDisc", (PyCFunction) _wrap_PyNs3QueueDiscClass_SetQueueDisc, METH_KEYWORDS|METH_VARARGS, "SetQueueDisc(qd)\n\ntype: qd: ns3::Ptr< ns3::QueueDisc >" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3QueueDiscClass__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3QueueDiscClass__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3QueueDiscClass__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3QueueDiscClass__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3QueueDiscClass__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3QueueDiscClass__tp_clear(PyNs3QueueDiscClass *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::QueueDiscClass *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3QueueDiscClass__tp_traverse(PyNs3QueueDiscClass *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3QueueDiscClass__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3QueueDiscClass__tp_dealloc(PyNs3QueueDiscClass *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3QueueDiscClass__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3QueueDiscClass__tp_richcompare (PyNs3QueueDiscClass *PYBINDGEN_UNUSED(self), PyNs3QueueDiscClass *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3QueueDiscClass_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3QueueDiscClass_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.QueueDiscClass",            /* tp_name */
    sizeof(PyNs3QueueDiscClass),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3QueueDiscClass__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "QueueDiscClass(arg0)\nQueueDiscClass()",                        /* Documentation string */
    (traverseproc)PyNs3QueueDiscClass__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3QueueDiscClass__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3QueueDiscClass__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3QueueDiscClass_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3QueueDiscClass, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3QueueDiscClass__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3RedQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3RedQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3RedQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3RedQueueDisc__PythonHelper::_wrap_DoInitialize(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3RedQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3RedQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3RedQueueDisc__PythonHelper::_wrap_NotifyNewAggregate(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3RedQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3RedQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3RedQueueDisc__PythonHelper::_wrap_DoDispose(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3RedQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3RedQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class RedQueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

void
PyNs3RedQueueDisc__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::RedQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::RedQueueDisc::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = (ns3::RedQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

bool
PyNs3RedQueueDisc__PythonHelper::CheckConfig()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::RedQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckConfig"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = (ns3::RedQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckConfig", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem >
PyNs3RedQueueDisc__PythonHelper::DoDequeue()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::RedQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDequeue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = (ns3::RedQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDequeue", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

bool
PyNs3RedQueueDisc__PythonHelper::DoEnqueue(ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::RedQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoEnqueue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = (ns3::RedQueueDisc*) this;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoEnqueue", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem const >
PyNs3RedQueueDisc__PythonHelper::DoPeek() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::RedQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoPeek"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = const_cast< ns3::RedQueueDisc* >((const ns3::RedQueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoPeek", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3RedQueueDisc__PythonHelper::InitializeParams()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::RedQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "InitializeParams"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = (ns3::RedQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "InitializeParams", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3RedQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

uint32_t
PyNs3RedQueueDisc__PythonHelper::GetQuota() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    uint32_t retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetQuota", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3RedQueueDisc__PythonHelper::SetQuota(uint32_t const quota)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::SetQuota(quota);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetQuota", (char *) "N", PyLong_FromUnsignedLong(quota));
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


void
PyNs3RedQueueDisc__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3RedQueueDisc__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3RedQueueDisc__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3RedQueueDisc__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3RedQueueDisc__tp_init__0(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3RedQueueDisc *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3RedQueueDisc_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3RedQueueDisc_Type)
    {
        self->obj = new PyNs3RedQueueDisc__PythonHelper(*((PyNs3RedQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3RedQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::RedQueueDisc(*((PyNs3RedQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

static int
_wrap_PyNs3RedQueueDisc__tp_init__1(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3RedQueueDisc_Type)
    {
        self->obj = new PyNs3RedQueueDisc__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3RedQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::RedQueueDisc();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

int _wrap_PyNs3RedQueueDisc__tp_init(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3RedQueueDisc__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3RedQueueDisc__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3RedQueueDisc_GetMode(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    ns3::Queue::QueueMode retval;
    
    retval = self->obj->GetMode();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_SetQueueLimit(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    unsigned int lim;
    const char *keywords[] = {"lim", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &lim)) {
        return NULL;
    }
    self->obj->SetQueueLimit(lim);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_GetQueueSize(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetQueueSize();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_SetAredBeta(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    double beta;
    const char *keywords[] = {"beta", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "d", (char **) keywords, &beta)) {
        return NULL;
    }
    self->obj->SetAredBeta(beta);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_SetAredAlpha(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    double alpha;
    const char *keywords[] = {"alpha", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "d", (char **) keywords, &alpha)) {
        return NULL;
    }
    self->obj->SetAredAlpha(alpha);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_GetAredAlpha(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    double retval;
    
    retval = self->obj->GetAredAlpha();
    py_retval = Py_BuildValue((char *) "d", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_SetTh(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    double minTh;
    double maxTh;
    const char *keywords[] = {"minTh", "maxTh", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "dd", (char **) keywords, &minTh, &maxTh)) {
        return NULL;
    }
    self->obj->SetTh(minTh, maxTh);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_GetStats(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3RedQueueDiscStats *py_Stats;
    
    ns3::RedQueueDisc::Stats retval = self->obj->GetStats();
    py_Stats = PyObject_New(PyNs3RedQueueDiscStats, &PyNs3RedQueueDiscStats_Type);
    py_Stats->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Stats->obj = new ns3::RedQueueDisc::Stats(retval);
    PyNs3RedQueueDiscStats_wrapper_registry[(void *) py_Stats->obj] = (PyObject *) py_Stats;
    py_retval = Py_BuildValue((char *) "N", py_Stats);
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_SetMode(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Queue::QueueMode mode;
    const char *keywords[] = {"mode", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &mode)) {
        return NULL;
    }
    self->obj->SetMode(mode);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_AssignStreams(PyNs3RedQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int64_t retval;
    int64_t stream;
    const char *keywords[] = {"stream", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "L", (char **) keywords, &stream)) {
        return NULL;
    }
    retval = self->obj->AssignStreams(stream);
    py_retval = Py_BuildValue((char *) "L", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::RedQueueDisc::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3RedQueueDisc_GetAredBeta(PyNs3RedQueueDisc *self)
{
    PyObject *py_retval;
    double retval;
    
    retval = self->obj->GetAredBeta();
    py_retval = Py_BuildValue((char *) "d", retval);
    return py_retval;
}


static PyObject*
_wrap_PyNs3RedQueueDisc__copy__(PyNs3RedQueueDisc *self)
{

    PyNs3RedQueueDisc *py_copy;
    py_copy = PyObject_GC_New(PyNs3RedQueueDisc, &PyNs3RedQueueDisc_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::RedQueueDisc(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3RedQueueDisc_methods[] = {
    {(char *) "GetMode", (PyCFunction) _wrap_PyNs3RedQueueDisc_GetMode, METH_NOARGS, "GetMode()\n\n" },
    {(char *) "SetQueueLimit", (PyCFunction) _wrap_PyNs3RedQueueDisc_SetQueueLimit, METH_KEYWORDS|METH_VARARGS, "SetQueueLimit(lim)\n\ntype: lim: uint32_t" },
    {(char *) "GetQueueSize", (PyCFunction) _wrap_PyNs3RedQueueDisc_GetQueueSize, METH_NOARGS, "GetQueueSize()\n\n" },
    {(char *) "SetAredBeta", (PyCFunction) _wrap_PyNs3RedQueueDisc_SetAredBeta, METH_KEYWORDS|METH_VARARGS, "SetAredBeta(beta)\n\ntype: beta: double" },
    {(char *) "SetAredAlpha", (PyCFunction) _wrap_PyNs3RedQueueDisc_SetAredAlpha, METH_KEYWORDS|METH_VARARGS, "SetAredAlpha(alpha)\n\ntype: alpha: double" },
    {(char *) "GetAredAlpha", (PyCFunction) _wrap_PyNs3RedQueueDisc_GetAredAlpha, METH_NOARGS, "GetAredAlpha()\n\n" },
    {(char *) "SetTh", (PyCFunction) _wrap_PyNs3RedQueueDisc_SetTh, METH_KEYWORDS|METH_VARARGS, "SetTh(minTh, maxTh)\n\ntype: minTh: double\ntype: maxTh: double" },
    {(char *) "GetStats", (PyCFunction) _wrap_PyNs3RedQueueDisc_GetStats, METH_NOARGS, "GetStats()\n\n" },
    {(char *) "SetMode", (PyCFunction) _wrap_PyNs3RedQueueDisc_SetMode, METH_KEYWORDS|METH_VARARGS, "SetMode(mode)\n\ntype: mode: ns3::Queue::QueueMode" },
    {(char *) "AssignStreams", (PyCFunction) _wrap_PyNs3RedQueueDisc_AssignStreams, METH_KEYWORDS|METH_VARARGS, "AssignStreams(stream)\n\ntype: stream: int64_t" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3RedQueueDisc_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "GetAredBeta", (PyCFunction) _wrap_PyNs3RedQueueDisc_GetAredBeta, METH_NOARGS, "GetAredBeta()\n\n" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3RedQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3RedQueueDisc__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3RedQueueDisc__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3RedQueueDisc__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3RedQueueDisc__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3RedQueueDisc__tp_clear(PyNs3RedQueueDisc *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::RedQueueDisc *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3RedQueueDisc__tp_traverse(PyNs3RedQueueDisc *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3RedQueueDisc__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3RedQueueDisc__tp_dealloc(PyNs3RedQueueDisc *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3RedQueueDisc__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3RedQueueDisc__tp_richcompare (PyNs3RedQueueDisc *PYBINDGEN_UNUSED(self), PyNs3RedQueueDisc *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3RedQueueDisc_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3RedQueueDisc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.RedQueueDisc",            /* tp_name */
    sizeof(PyNs3RedQueueDisc),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3RedQueueDisc__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "RedQueueDisc(arg0)\nRedQueueDisc()",                        /* Documentation string */
    (traverseproc)PyNs3RedQueueDisc__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3RedQueueDisc__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3RedQueueDisc__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3RedQueueDisc_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3RedQueueDisc, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3RedQueueDisc__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};



std::map<void*, PyObject*> PyNs3RedQueueDiscStats_wrapper_registry;
static PyObject* _wrap_PyNs3RedQueueDiscStats__get_forcedDrop(PyNs3RedQueueDiscStats *self, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(self->obj->forcedDrop));
    return py_retval;
}
static int _wrap_PyNs3RedQueueDiscStats__set_forcedDrop(PyNs3RedQueueDiscStats *self, PyObject *value, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &self->obj->forcedDrop)) {
        Py_DECREF(py_retval);
        return -1;
    }
    Py_DECREF(py_retval);
    return 0;
}
static PyObject* _wrap_PyNs3RedQueueDiscStats__get_qLimDrop(PyNs3RedQueueDiscStats *self, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(self->obj->qLimDrop));
    return py_retval;
}
static int _wrap_PyNs3RedQueueDiscStats__set_qLimDrop(PyNs3RedQueueDiscStats *self, PyObject *value, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &self->obj->qLimDrop)) {
        Py_DECREF(py_retval);
        return -1;
    }
    Py_DECREF(py_retval);
    return 0;
}
static PyObject* _wrap_PyNs3RedQueueDiscStats__get_unforcedDrop(PyNs3RedQueueDiscStats *self, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(self->obj->unforcedDrop));
    return py_retval;
}
static int _wrap_PyNs3RedQueueDiscStats__set_unforcedDrop(PyNs3RedQueueDiscStats *self, PyObject *value, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &self->obj->unforcedDrop)) {
        Py_DECREF(py_retval);
        return -1;
    }
    Py_DECREF(py_retval);
    return 0;
}
static PyGetSetDef PyNs3RedQueueDiscStats__getsets[] = {
    {
        (char*) "qLimDrop", /* attribute name */
        (getter) _wrap_PyNs3RedQueueDiscStats__get_qLimDrop, /* C function to get the attribute */
        (setter) _wrap_PyNs3RedQueueDiscStats__set_qLimDrop, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "forcedDrop", /* attribute name */
        (getter) _wrap_PyNs3RedQueueDiscStats__get_forcedDrop, /* C function to get the attribute */
        (setter) _wrap_PyNs3RedQueueDiscStats__set_forcedDrop, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "unforcedDrop", /* attribute name */
        (getter) _wrap_PyNs3RedQueueDiscStats__get_unforcedDrop, /* C function to get the attribute */
        (setter) _wrap_PyNs3RedQueueDiscStats__set_unforcedDrop, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};


static int
_wrap_PyNs3RedQueueDiscStats__tp_init__0(PyNs3RedQueueDiscStats *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::RedQueueDisc::Stats();
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3RedQueueDiscStats__tp_init__1(PyNs3RedQueueDiscStats *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3RedQueueDiscStats *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3RedQueueDiscStats_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::RedQueueDisc::Stats(*((PyNs3RedQueueDiscStats *) arg0)->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

int _wrap_PyNs3RedQueueDiscStats__tp_init(PyNs3RedQueueDiscStats *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3RedQueueDiscStats__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3RedQueueDiscStats__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


static PyObject*
_wrap_PyNs3RedQueueDiscStats__copy__(PyNs3RedQueueDiscStats *self)
{

    PyNs3RedQueueDiscStats *py_copy;
    py_copy = PyObject_New(PyNs3RedQueueDiscStats, &PyNs3RedQueueDiscStats_Type);
    py_copy->obj = new ns3::RedQueueDisc::Stats(*self->obj);
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3RedQueueDiscStats_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3RedQueueDiscStats_methods[] = {
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3RedQueueDiscStats__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
_wrap_PyNs3RedQueueDiscStats__tp_dealloc(PyNs3RedQueueDiscStats *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3RedQueueDiscStats_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3RedQueueDiscStats_wrapper_registry.end()) {
        PyNs3RedQueueDiscStats_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
        ns3::RedQueueDisc::Stats *tmp = self->obj;
        self->obj = NULL;
        if (!(self->flags&PYBINDGEN_WRAPPER_FLAG_OBJECT_NOT_OWNED)) {
            delete tmp;
        }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3RedQueueDiscStats__tp_richcompare (PyNs3RedQueueDiscStats *PYBINDGEN_UNUSED(self), PyNs3RedQueueDiscStats *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3RedQueueDiscStats_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3RedQueueDiscStats_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.RedQueueDisc.Stats",            /* tp_name */
    sizeof(PyNs3RedQueueDiscStats),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3RedQueueDiscStats__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    "Stats(arg0)\nStats()",                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3RedQueueDiscStats__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3RedQueueDiscStats_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    PyNs3RedQueueDiscStats__getsets,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3RedQueueDiscStats__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3TrafficControlLayer__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3TrafficControlLayer *self)
{
    PyObject *py_retval;
    PyNs3TrafficControlLayer__PythonHelper *helper = dynamic_cast< PyNs3TrafficControlLayer__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3TrafficControlLayer__PythonHelper::_wrap_DoInitialize(PyNs3TrafficControlLayer *self)
{
    PyObject *py_retval;
    PyNs3TrafficControlLayer__PythonHelper *helper = dynamic_cast< PyNs3TrafficControlLayer__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class TrafficControlLayer is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3TrafficControlLayer__PythonHelper::_wrap_NotifyNewAggregate(PyNs3TrafficControlLayer *self)
{
    PyObject *py_retval;
    PyNs3TrafficControlLayer__PythonHelper *helper = dynamic_cast< PyNs3TrafficControlLayer__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class TrafficControlLayer is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3TrafficControlLayer__PythonHelper::_wrap_DoDispose(PyNs3TrafficControlLayer *self)
{
    PyObject *py_retval;
    PyNs3TrafficControlLayer__PythonHelper *helper = dynamic_cast< PyNs3TrafficControlLayer__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class TrafficControlLayer is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

void
PyNs3TrafficControlLayer__PythonHelper::DeleteRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice > device)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DeleteRootQueueDiscOnDevice"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::DeleteRootQueueDiscOnDevice(device);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (device)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (device));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DeleteRootQueueDiscOnDevice", (char *) "N", py_NetDevice);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3TrafficControlLayer__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::TrafficControlLayer::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = const_cast< ns3::TrafficControlLayer* >((const ns3::TrafficControlLayer*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::TrafficControlLayer::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::TrafficControlLayer::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDisc >
PyNs3TrafficControlLayer__PythonHelper::GetRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice > device) const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDisc > retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyNs3QueueDisc *tmp_QueueDisc;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetRootQueueDiscOnDevice"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::TrafficControlLayer::GetRootQueueDiscOnDevice(device);
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = const_cast< ns3::TrafficControlLayer* >((const ns3::TrafficControlLayer*) this);
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (device)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (device));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetRootQueueDiscOnDevice", (char *) "N", py_NetDevice);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::TrafficControlLayer::GetRootQueueDiscOnDevice(device);
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDisc_Type, &tmp_QueueDisc)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::TrafficControlLayer::GetRootQueueDiscOnDevice(device);
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDisc  > (tmp_QueueDisc->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3TrafficControlLayer__PythonHelper::Receive(ns3::Ptr< ns3::NetDevice > device, ns3::Ptr< ns3::Packet const > p, uint16_t protocol, ns3::Address const & from, ns3::Address const & to, ns3::NetDevice::PacketType packetType)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyNs3Packet *py_Packet;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter2;
    PyTypeObject *wrapper_type2 = 0;
    PyNs3Address *py_Address;
    PyNs3Address *py_Address2;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "Receive"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::Receive(device, p, protocol, from, to, packetType);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (device)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (device));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    wrapper_lookup_iter2 = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::Packet *> (ns3::PeekPointer (p)));
    if (wrapper_lookup_iter2 == PyNs3Empty_wrapper_registry.end()) {
        py_Packet = NULL;
    } else {
        py_Packet = (PyNs3Packet *) wrapper_lookup_iter2->second;
        Py_INCREF(py_Packet);
    }
    
    if (py_Packet == NULL)
    {
        wrapper_type2 = PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::Packet *> (ns3::PeekPointer (p))), &PyNs3Packet_Type);
        py_Packet = PyObject_New(PyNs3Packet, wrapper_type2);
    
        py_Packet->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::Packet *> (ns3::PeekPointer (p))->Ref();
        py_Packet->obj = const_cast<ns3::Packet *> (ns3::PeekPointer (p));
        PyNs3Empty_wrapper_registry[(void *) py_Packet->obj] = (PyObject *) py_Packet;
    }
    py_Address = PyObject_New(PyNs3Address, &PyNs3Address_Type);
    py_Address->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Address->obj = new ns3::Address(from);
    PyNs3Address_wrapper_registry[(void *) py_Address->obj] = (PyObject *) py_Address;
    py_Address2 = PyObject_New(PyNs3Address, &PyNs3Address_Type);
    py_Address2->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Address2->obj = new ns3::Address(to);
    PyNs3Address_wrapper_registry[(void *) py_Address2->obj] = (PyObject *) py_Address2;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "Receive", (char *) "NNiNNi", py_NetDevice, py_Packet, (int) protocol, py_Address, py_Address2, packetType);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::Send(ns3::Ptr< ns3::NetDevice > device, ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter2;
    PyTypeObject *wrapper_type2 = 0;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "Send"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::Send(device, item);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (device)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (device));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    wrapper_lookup_iter2 = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter2 == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter2->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type2 = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type2);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "Send", (char *) "NN", py_NetDevice, py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::SetRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice > device, ns3::Ptr< ns3::QueueDisc > qDisc)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyNs3QueueDisc *py_QueueDisc;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter2;
    PyTypeObject *wrapper_type2 = 0;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetRootQueueDiscOnDevice"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::SetRootQueueDiscOnDevice(device, qDisc);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (device)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (device));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    if (typeid(*(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc)))).name() == typeid(PyNs3QueueDisc__PythonHelper).name())
    {
        py_QueueDisc = (PyNs3QueueDisc*) (((PyNs3QueueDisc__PythonHelper*) const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc)))->m_pyself);
        py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc));
        Py_INCREF(py_QueueDisc);
    } else {
        wrapper_lookup_iter2 = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc)));
        if (wrapper_lookup_iter2 == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDisc = NULL;
        } else {
            py_QueueDisc = (PyNs3QueueDisc *) wrapper_lookup_iter2->second;
            Py_INCREF(py_QueueDisc);
        }
    
        if (py_QueueDisc == NULL)
        {
            wrapper_type2 = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc))), &PyNs3QueueDisc_Type);
            py_QueueDisc = PyObject_GC_New(PyNs3QueueDisc, wrapper_type2);
            py_QueueDisc->inst_dict = NULL;
    
            py_QueueDisc->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc))->Ref();
            py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (qDisc));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDisc->obj] = (PyObject *) py_QueueDisc;
        }
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetRootQueueDiscOnDevice", (char *) "NN", py_NetDevice, py_QueueDisc);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::SetupDevice(ns3::Ptr< ns3::NetDevice > device)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    PyNs3NetDevice *py_NetDevice;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetupDevice"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::SetupDevice(device);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::NetDevice *> (ns3::PeekPointer (device)));
    if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
        py_NetDevice = NULL;
    } else {
        py_NetDevice = (PyNs3NetDevice *) wrapper_lookup_iter->second;
        Py_INCREF(py_NetDevice);
    }
    
    if (py_NetDevice == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid(*const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))), &PyNs3NetDevice_Type);
        py_NetDevice = PyObject_GC_New(PyNs3NetDevice, wrapper_type);
        py_NetDevice->inst_dict = NULL;
    
        py_NetDevice->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::NetDevice *> (ns3::PeekPointer (device))->Ref();
        py_NetDevice->obj = const_cast<ns3::NetDevice *> (ns3::PeekPointer (device));
        PyNs3ObjectBase_wrapper_registry[(void *) py_NetDevice->obj] = (PyObject *) py_NetDevice;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetupDevice", (char *) "N", py_NetDevice);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::TrafficControlLayer *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::TrafficControlLayer::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj;
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = (ns3::TrafficControlLayer*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3TrafficControlLayer* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3TrafficControlLayer__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

static int
_wrap_PyNs3TrafficControlLayer__tp_init(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3TrafficControlLayer_Type)
    {
        self->obj = new PyNs3TrafficControlLayer__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3TrafficControlLayer__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::TrafficControlLayer();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_SetupDevice(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    const char *keywords[] = {"device", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDevice_Type, &device)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    (helper_class == NULL)? (self->obj->SetupDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr))) : (self->obj->ns3::TrafficControlLayer::SetupDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr)));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_GetRootQueueDiscOnDevice(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDisc > retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    const char *keywords[] = {"device", NULL};
    PyNs3QueueDisc *py_QueueDisc;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDevice_Type, &device)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    retval = (helper_class == NULL)? (self->obj->GetRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr))) : (self->obj->ns3::TrafficControlLayer::GetRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr)));
    if (!(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))).name() == typeid(PyNs3QueueDisc__PythonHelper).name())
    {
        py_QueueDisc = reinterpret_cast< PyNs3QueueDisc* >(reinterpret_cast< PyNs3QueueDisc__PythonHelper* >(const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))->m_pyself);
        py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
        Py_INCREF(py_QueueDisc);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDisc = NULL;
        } else {
            py_QueueDisc = (PyNs3QueueDisc *) wrapper_lookup_iter->second;
            Py_INCREF(py_QueueDisc);
        }
    
        if (py_QueueDisc == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval)))), &PyNs3QueueDisc_Type);
            py_QueueDisc = PyObject_GC_New(PyNs3QueueDisc, wrapper_type);
            py_QueueDisc->inst_dict = NULL;
    
            py_QueueDisc->inst_dict = NULL;
            py_QueueDisc->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval))->Ref();
            py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer (retval));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDisc->obj] = (PyObject *) py_QueueDisc;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDisc);
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_Receive(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    PyNs3Packet *p;
    ns3::Packet *p_ptr;
    int protocol;
    PyObject *from;
    ns3::Address from2;
    PyObject *to;
    ns3::Address to2;
    ns3::NetDevice::PacketType packetType;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    const char *keywords[] = {"device", "p", "protocol", "from", "to", "packetType", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!iOOi", (char **) keywords, &PyNs3NetDevice_Type, &device, &PyNs3Packet_Type, &p, &protocol, &from, &to, &packetType)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    p_ptr = (p ? p->obj : NULL);
    if (protocol > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    if (PyObject_IsInstance(from, (PyObject*) &PyNs3Address_Type)) {
        from2 = *((PyNs3Address *) from)->obj;
    } else if (PyObject_IsInstance(from, (PyObject*) &PyNs3Ipv4Address_Type)) {
        from2 = *((PyNs3Ipv4Address *) from)->obj;
    } else if (PyObject_IsInstance(from, (PyObject*) &PyNs3Ipv6Address_Type)) {
        from2 = *((PyNs3Ipv6Address *) from)->obj;
    } else if (PyObject_IsInstance(from, (PyObject*) &PyNs3Mac48Address_Type)) {
        from2 = *((PyNs3Mac48Address *) from)->obj;
    } else {
    
        PyErr_Format(PyExc_TypeError, "parameter must an instance of one of the types (Address, Ipv4Address, Ipv6Address, Mac48Address), not %s", Py_TYPE(from)->tp_name);
        return NULL;
    }
    if (PyObject_IsInstance(to, (PyObject*) &PyNs3Address_Type)) {
        to2 = *((PyNs3Address *) to)->obj;
    } else if (PyObject_IsInstance(to, (PyObject*) &PyNs3Ipv4Address_Type)) {
        to2 = *((PyNs3Ipv4Address *) to)->obj;
    } else if (PyObject_IsInstance(to, (PyObject*) &PyNs3Ipv6Address_Type)) {
        to2 = *((PyNs3Ipv6Address *) to)->obj;
    } else if (PyObject_IsInstance(to, (PyObject*) &PyNs3Mac48Address_Type)) {
        to2 = *((PyNs3Mac48Address *) to)->obj;
    } else {
    
        PyErr_Format(PyExc_TypeError, "parameter must an instance of one of the types (Address, Ipv4Address, Ipv6Address, Mac48Address), not %s", Py_TYPE(to)->tp_name);
        return NULL;
    }
    (helper_class == NULL)? (self->obj->Receive(ns3::Ptr< ns3::NetDevice  > (device_ptr), ns3::Ptr< ns3::Packet  > (p_ptr), protocol, from2, to2, packetType)) : (self->obj->ns3::TrafficControlLayer::Receive(ns3::Ptr< ns3::NetDevice  > (device_ptr), ns3::Ptr< ns3::Packet  > (p_ptr), protocol, from2, to2, packetType));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_RegisterProtocolHandler(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyObject *handler;
    ns3::Ptr<PythonCallbackImpl1> handler_cb_impl;
    int protocolType;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    const char *keywords[] = {"handler", "protocolType", "device", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "OiO!", (char **) keywords, &handler, &protocolType, &PyNs3NetDevice_Type, &device)) {
        return NULL;
    }
    if (!PyCallable_Check(handler)) {
        PyErr_SetString(PyExc_TypeError, "parameter 'handler' must be callbale");
        return NULL;
    }
    handler_cb_impl = ns3::Create<PythonCallbackImpl1> (handler);
    if (protocolType > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    self->obj->RegisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> (handler_cb_impl), protocolType, ns3::Ptr< ns3::NetDevice  > (device_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_SetRootQueueDiscOnDevice(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    PyNs3QueueDisc *qDisc;
    ns3::QueueDisc *qDisc_ptr;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    const char *keywords[] = {"device", "qDisc", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!", (char **) keywords, &PyNs3NetDevice_Type, &device, &PyNs3QueueDisc_Type, &qDisc)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    qDisc_ptr = (qDisc ? qDisc->obj : NULL);
    (helper_class == NULL)? (self->obj->SetRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr), ns3::Ptr< ns3::QueueDisc  > (qDisc_ptr))) : (self->obj->ns3::TrafficControlLayer::SetRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr), ns3::Ptr< ns3::QueueDisc  > (qDisc_ptr)));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_Send(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    PyNs3QueueDiscItem *item;
    ns3::QueueDiscItem *item_ptr;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    const char *keywords[] = {"device", "item", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!", (char **) keywords, &PyNs3NetDevice_Type, &device, &PyNs3QueueDiscItem_Type, &item)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    item_ptr = (item ? item->obj : NULL);
    (helper_class == NULL)? (self->obj->Send(ns3::Ptr< ns3::NetDevice  > (device_ptr), ns3::Ptr< ns3::QueueDiscItem  > (item_ptr))) : (self->obj->ns3::TrafficControlLayer::Send(ns3::Ptr< ns3::NetDevice  > (device_ptr), ns3::Ptr< ns3::QueueDiscItem  > (item_ptr)));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_SetNode(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3Node *node;
    ns3::Node *node_ptr;
    const char *keywords[] = {"node", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3Node_Type, &node)) {
        return NULL;
    }
    node_ptr = (node ? node->obj : NULL);
    self->obj->SetNode(ns3::Ptr< ns3::Node  > (node_ptr));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_GetInstanceTypeId(PyNs3TrafficControlLayer *self)
{
    PyObject *py_retval;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = (helper_class == NULL)? (self->obj->GetInstanceTypeId()) : (self->obj->ns3::TrafficControlLayer::GetInstanceTypeId());
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_DeleteRootQueueDiscOnDevice(PyNs3TrafficControlLayer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyNs3NetDevice *device;
    ns3::NetDevice *device_ptr;
    PyNs3TrafficControlLayer__PythonHelper *helper_class = dynamic_cast<PyNs3TrafficControlLayer__PythonHelper*> (self->obj);
    const char *keywords[] = {"device", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3NetDevice_Type, &device)) {
        return NULL;
    }
    device_ptr = (device ? device->obj : NULL);
    (helper_class == NULL)? (self->obj->DeleteRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr))) : (self->obj->ns3::TrafficControlLayer::DeleteRootQueueDiscOnDevice(ns3::Ptr< ns3::NetDevice  > (device_ptr)));
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3TrafficControlLayer_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::TrafficControlLayer::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}

static PyMethodDef PyNs3TrafficControlLayer_methods[] = {
    {(char *) "SetupDevice", (PyCFunction) _wrap_PyNs3TrafficControlLayer_SetupDevice, METH_KEYWORDS|METH_VARARGS, "SetupDevice(device)\n\ntype: device: ns3::Ptr< ns3::NetDevice >" },
    {(char *) "GetRootQueueDiscOnDevice", (PyCFunction) _wrap_PyNs3TrafficControlLayer_GetRootQueueDiscOnDevice, METH_KEYWORDS|METH_VARARGS, "GetRootQueueDiscOnDevice(device)\n\ntype: device: ns3::Ptr< ns3::NetDevice >" },
    {(char *) "Receive", (PyCFunction) _wrap_PyNs3TrafficControlLayer_Receive, METH_KEYWORDS|METH_VARARGS, "Receive(device, p, protocol, from, to, packetType)\n\ntype: device: ns3::Ptr< ns3::NetDevice >\ntype: p: ns3::Ptr< ns3::Packet const >\ntype: protocol: uint16_t\ntype: from: ns3::Address const &\ntype: to: ns3::Address const &\ntype: packetType: ns3::NetDevice::PacketType" },
    {(char *) "RegisterProtocolHandler", (PyCFunction) _wrap_PyNs3TrafficControlLayer_RegisterProtocolHandler, METH_KEYWORDS|METH_VARARGS, "RegisterProtocolHandler(handler, protocolType, device)\n\ntype: handler: ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >\ntype: protocolType: uint16_t\ntype: device: ns3::Ptr< ns3::NetDevice >" },
    {(char *) "SetRootQueueDiscOnDevice", (PyCFunction) _wrap_PyNs3TrafficControlLayer_SetRootQueueDiscOnDevice, METH_KEYWORDS|METH_VARARGS, "SetRootQueueDiscOnDevice(device, qDisc)\n\ntype: device: ns3::Ptr< ns3::NetDevice >\ntype: qDisc: ns3::Ptr< ns3::QueueDisc >" },
    {(char *) "Send", (PyCFunction) _wrap_PyNs3TrafficControlLayer_Send, METH_KEYWORDS|METH_VARARGS, "Send(device, item)\n\ntype: device: ns3::Ptr< ns3::NetDevice >\ntype: item: ns3::Ptr< ns3::QueueDiscItem >" },
    {(char *) "SetNode", (PyCFunction) _wrap_PyNs3TrafficControlLayer_SetNode, METH_KEYWORDS|METH_VARARGS, "SetNode(node)\n\ntype: node: ns3::Ptr< ns3::Node >" },
    {(char *) "GetInstanceTypeId", (PyCFunction) _wrap_PyNs3TrafficControlLayer_GetInstanceTypeId, METH_NOARGS, "GetInstanceTypeId()\n\n" },
    {(char *) "DeleteRootQueueDiscOnDevice", (PyCFunction) _wrap_PyNs3TrafficControlLayer_DeleteRootQueueDiscOnDevice, METH_KEYWORDS|METH_VARARGS, "DeleteRootQueueDiscOnDevice(device)\n\ntype: device: ns3::Ptr< ns3::NetDevice >" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3TrafficControlLayer_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3TrafficControlLayer__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3TrafficControlLayer__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3TrafficControlLayer__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3TrafficControlLayer__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {NULL, NULL, 0, NULL}
};

static void
PyNs3TrafficControlLayer__tp_clear(PyNs3TrafficControlLayer *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::TrafficControlLayer *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3TrafficControlLayer__tp_traverse(PyNs3TrafficControlLayer *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3TrafficControlLayer__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3TrafficControlLayer__tp_dealloc(PyNs3TrafficControlLayer *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3TrafficControlLayer__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3TrafficControlLayer__tp_richcompare (PyNs3TrafficControlLayer *PYBINDGEN_UNUSED(self), PyNs3TrafficControlLayer *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3TrafficControlLayer_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3TrafficControlLayer_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.TrafficControlLayer",            /* tp_name */
    sizeof(PyNs3TrafficControlLayer),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3TrafficControlLayer__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "TrafficControlLayer()",                        /* Documentation string */
    (traverseproc)PyNs3TrafficControlLayer__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3TrafficControlLayer__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3TrafficControlLayer__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3TrafficControlLayer_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3TrafficControlLayer, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3TrafficControlLayer__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3CoDelQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3CoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3CoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3CoDelQueueDisc__PythonHelper::_wrap_DoInitialize(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3CoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3CoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3CoDelQueueDisc__PythonHelper::_wrap_NotifyNewAggregate(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3CoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3CoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3CoDelQueueDisc__PythonHelper::_wrap_DoDispose(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3CoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3CoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

bool
PyNs3CoDelQueueDisc__PythonHelper::CheckConfig()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::CoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckConfig"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = (ns3::CoDelQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckConfig", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem >
PyNs3CoDelQueueDisc__PythonHelper::DoDequeue()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::CoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDequeue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = (ns3::CoDelQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDequeue", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

bool
PyNs3CoDelQueueDisc__PythonHelper::DoEnqueue(ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::CoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoEnqueue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = (ns3::CoDelQueueDisc*) this;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoEnqueue", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem const >
PyNs3CoDelQueueDisc__PythonHelper::DoPeek() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::CoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoPeek"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = const_cast< ns3::CoDelQueueDisc* >((const ns3::CoDelQueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoPeek", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3CoDelQueueDisc__PythonHelper::InitializeParams()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::CoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "InitializeParams"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = (ns3::CoDelQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "InitializeParams", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3CoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

uint32_t
PyNs3CoDelQueueDisc__PythonHelper::GetQuota() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    uint32_t retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetQuota", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3CoDelQueueDisc__PythonHelper::SetQuota(uint32_t const quota)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::SetQuota(quota);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetQuota", (char *) "N", PyLong_FromUnsignedLong(quota));
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


void
PyNs3CoDelQueueDisc__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3CoDelQueueDisc__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3CoDelQueueDisc__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3CoDelQueueDisc__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3CoDelQueueDisc__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3CoDelQueueDisc__tp_init__0(PyNs3CoDelQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3CoDelQueueDisc *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3CoDelQueueDisc_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3CoDelQueueDisc_Type)
    {
        self->obj = new PyNs3CoDelQueueDisc__PythonHelper(*((PyNs3CoDelQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3CoDelQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::CoDelQueueDisc(*((PyNs3CoDelQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

static int
_wrap_PyNs3CoDelQueueDisc__tp_init__1(PyNs3CoDelQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3CoDelQueueDisc_Type)
    {
        self->obj = new PyNs3CoDelQueueDisc__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3CoDelQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::CoDelQueueDisc();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

int _wrap_PyNs3CoDelQueueDisc__tp_init(PyNs3CoDelQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3CoDelQueueDisc__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3CoDelQueueDisc__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetMode(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    ns3::Queue::QueueMode retval;
    
    retval = self->obj->GetMode();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetInterval(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3Time *py_Time;
    
    ns3::Time retval = self->obj->GetInterval();
    py_Time = PyObject_New(PyNs3Time, &PyNs3Time_Type);
    py_Time->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Time->obj = new ns3::Time(retval);
    PyNs3Time_wrapper_registry[(void *) py_Time->obj] = (PyObject *) py_Time;
    py_retval = Py_BuildValue((char *) "N", py_Time);
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetDropNext(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetDropNext();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetQueueSize(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetQueueSize();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetDropCount(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetDropCount();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetTarget(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3Time *py_Time;
    
    ns3::Time retval = self->obj->GetTarget();
    py_Time = PyObject_New(PyNs3Time, &PyNs3Time_Type);
    py_Time->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Time->obj = new ns3::Time(retval);
    PyNs3Time_wrapper_registry[(void *) py_Time->obj] = (PyObject *) py_Time;
    py_retval = Py_BuildValue((char *) "N", py_Time);
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetDropOverLimit(PyNs3CoDelQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetDropOverLimit();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_SetMode(PyNs3CoDelQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Queue::QueueMode mode;
    const char *keywords[] = {"mode", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &mode)) {
        return NULL;
    }
    self->obj->SetMode(mode);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3CoDelQueueDisc_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::CoDelQueueDisc::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


static PyObject*
_wrap_PyNs3CoDelQueueDisc__copy__(PyNs3CoDelQueueDisc *self)
{

    PyNs3CoDelQueueDisc *py_copy;
    py_copy = PyObject_GC_New(PyNs3CoDelQueueDisc, &PyNs3CoDelQueueDisc_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::CoDelQueueDisc(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3CoDelQueueDisc_methods[] = {
    {(char *) "GetMode", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetMode, METH_NOARGS, "GetMode()\n\n" },
    {(char *) "GetInterval", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetInterval, METH_NOARGS, "GetInterval()\n\n" },
    {(char *) "GetDropNext", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetDropNext, METH_NOARGS, "GetDropNext()\n\n" },
    {(char *) "GetQueueSize", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetQueueSize, METH_NOARGS, "GetQueueSize()\n\n" },
    {(char *) "GetDropCount", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetDropCount, METH_NOARGS, "GetDropCount()\n\n" },
    {(char *) "GetTarget", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetTarget, METH_NOARGS, "GetTarget()\n\n" },
    {(char *) "GetDropOverLimit", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetDropOverLimit, METH_NOARGS, "GetDropOverLimit()\n\n" },
    {(char *) "SetMode", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_SetMode, METH_KEYWORDS|METH_VARARGS, "SetMode(mode)\n\ntype: mode: ns3::Queue::QueueMode" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3CoDelQueueDisc_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3CoDelQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3CoDelQueueDisc__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3CoDelQueueDisc__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3CoDelQueueDisc__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3CoDelQueueDisc__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3CoDelQueueDisc__tp_clear(PyNs3CoDelQueueDisc *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::CoDelQueueDisc *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3CoDelQueueDisc__tp_traverse(PyNs3CoDelQueueDisc *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3CoDelQueueDisc__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3CoDelQueueDisc__tp_dealloc(PyNs3CoDelQueueDisc *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3CoDelQueueDisc__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3CoDelQueueDisc__tp_richcompare (PyNs3CoDelQueueDisc *PYBINDGEN_UNUSED(self), PyNs3CoDelQueueDisc *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3CoDelQueueDisc_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3CoDelQueueDisc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.CoDelQueueDisc",            /* tp_name */
    sizeof(PyNs3CoDelQueueDisc),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3CoDelQueueDisc__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "CoDelQueueDisc(arg0)\nCoDelQueueDisc()",                        /* Documentation string */
    (traverseproc)PyNs3CoDelQueueDisc__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3CoDelQueueDisc__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3CoDelQueueDisc__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3CoDelQueueDisc_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3CoDelQueueDisc, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3CoDelQueueDisc__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};





static int
_wrap_PyNs3FqCoDelFlow__tp_init__0(PyNs3FqCoDelFlow *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3FqCoDelFlow *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3FqCoDelFlow_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::FqCoDelFlow(*((PyNs3FqCoDelFlow *) arg0)->obj);
    self->obj->Ref ();
    ns3::CompleteConstruct(self->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3FqCoDelFlow__tp_init__1(PyNs3FqCoDelFlow *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::FqCoDelFlow();
    self->obj->Ref ();
    ns3::CompleteConstruct(self->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

int _wrap_PyNs3FqCoDelFlow__tp_init(PyNs3FqCoDelFlow *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3FqCoDelFlow__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3FqCoDelFlow__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3FqCoDelFlow_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::FqCoDelFlow::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelFlow_GetStatus(PyNs3FqCoDelFlow *self)
{
    PyObject *py_retval;
    ns3::FqCoDelFlow::FlowStatus retval;
    
    retval = self->obj->GetStatus();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelFlow_SetStatus(PyNs3FqCoDelFlow *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::FqCoDelFlow::FlowStatus status;
    const char *keywords[] = {"status", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &status)) {
        return NULL;
    }
    self->obj->SetStatus(status);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelFlow_GetDeficit(PyNs3FqCoDelFlow *self)
{
    PyObject *py_retval;
    int32_t retval;
    
    retval = self->obj->GetDeficit();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelFlow_IncreaseDeficit(PyNs3FqCoDelFlow *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int32_t deficit;
    const char *keywords[] = {"deficit", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &deficit)) {
        return NULL;
    }
    self->obj->IncreaseDeficit(deficit);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelFlow_SetDeficit(PyNs3FqCoDelFlow *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    unsigned int deficit;
    const char *keywords[] = {"deficit", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &deficit)) {
        return NULL;
    }
    self->obj->SetDeficit(deficit);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


static PyObject*
_wrap_PyNs3FqCoDelFlow__copy__(PyNs3FqCoDelFlow *self)
{

    PyNs3FqCoDelFlow *py_copy;
    py_copy = PyObject_GC_New(PyNs3FqCoDelFlow, &PyNs3FqCoDelFlow_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::FqCoDelFlow(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3FqCoDelFlow_methods[] = {
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3FqCoDelFlow_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "GetStatus", (PyCFunction) _wrap_PyNs3FqCoDelFlow_GetStatus, METH_NOARGS, "GetStatus()\n\n" },
    {(char *) "SetStatus", (PyCFunction) _wrap_PyNs3FqCoDelFlow_SetStatus, METH_KEYWORDS|METH_VARARGS, "SetStatus(status)\n\ntype: status: ns3::FqCoDelFlow::FlowStatus" },
    {(char *) "GetDeficit", (PyCFunction) _wrap_PyNs3FqCoDelFlow_GetDeficit, METH_NOARGS, "GetDeficit()\n\n" },
    {(char *) "IncreaseDeficit", (PyCFunction) _wrap_PyNs3FqCoDelFlow_IncreaseDeficit, METH_KEYWORDS|METH_VARARGS, "IncreaseDeficit(deficit)\n\ntype: deficit: int32_t" },
    {(char *) "SetDeficit", (PyCFunction) _wrap_PyNs3FqCoDelFlow_SetDeficit, METH_KEYWORDS|METH_VARARGS, "SetDeficit(deficit)\n\ntype: deficit: uint32_t" },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3FqCoDelFlow__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3FqCoDelFlow__tp_clear(PyNs3FqCoDelFlow *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::FqCoDelFlow *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3FqCoDelFlow__tp_traverse(PyNs3FqCoDelFlow *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    return 0;
}


static void
_wrap_PyNs3FqCoDelFlow__tp_dealloc(PyNs3FqCoDelFlow *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3FqCoDelFlow__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3FqCoDelFlow__tp_richcompare (PyNs3FqCoDelFlow *PYBINDGEN_UNUSED(self), PyNs3FqCoDelFlow *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3FqCoDelFlow_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3FqCoDelFlow_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.FqCoDelFlow",            /* tp_name */
    sizeof(PyNs3FqCoDelFlow),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3FqCoDelFlow__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "FqCoDelFlow(arg0)\nFqCoDelFlow()",                        /* Documentation string */
    (traverseproc)PyNs3FqCoDelFlow__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3FqCoDelFlow__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3FqCoDelFlow__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3FqCoDelFlow_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3FqCoDelFlow, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3FqCoDelFlow__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3FqCoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3FqCoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3FqCoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_DoInitialize(PyNs3FqCoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3FqCoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3FqCoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_NotifyNewAggregate(PyNs3FqCoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3FqCoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3FqCoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_DoDispose(PyNs3FqCoDelQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3FqCoDelQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3FqCoDelQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

bool
PyNs3FqCoDelQueueDisc__PythonHelper::CheckConfig()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::FqCoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckConfig"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = (ns3::FqCoDelQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckConfig", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem >
PyNs3FqCoDelQueueDisc__PythonHelper::DoDequeue()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::FqCoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDequeue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = (ns3::FqCoDelQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDequeue", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

bool
PyNs3FqCoDelQueueDisc__PythonHelper::DoEnqueue(ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::FqCoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoEnqueue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = (ns3::FqCoDelQueueDisc*) this;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoEnqueue", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem const >
PyNs3FqCoDelQueueDisc__PythonHelper::DoPeek() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::FqCoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoPeek"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = const_cast< ns3::FqCoDelQueueDisc* >((const ns3::FqCoDelQueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoPeek", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3FqCoDelQueueDisc__PythonHelper::InitializeParams()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::FqCoDelQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "InitializeParams"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = (ns3::FqCoDelQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "InitializeParams", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3FqCoDelQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

uint32_t
PyNs3FqCoDelQueueDisc__PythonHelper::GetQuota() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    uint32_t retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetQuota", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3FqCoDelQueueDisc__PythonHelper::SetQuota(uint32_t const quota)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::SetQuota(quota);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetQuota", (char *) "N", PyLong_FromUnsignedLong(quota));
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


void
PyNs3FqCoDelQueueDisc__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3FqCoDelQueueDisc__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3FqCoDelQueueDisc__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3FqCoDelQueueDisc__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3FqCoDelQueueDisc__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3FqCoDelQueueDisc__tp_init__0(PyNs3FqCoDelQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3FqCoDelQueueDisc *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3FqCoDelQueueDisc_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3FqCoDelQueueDisc_Type)
    {
        self->obj = new PyNs3FqCoDelQueueDisc__PythonHelper(*((PyNs3FqCoDelQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3FqCoDelQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::FqCoDelQueueDisc(*((PyNs3FqCoDelQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

static int
_wrap_PyNs3FqCoDelQueueDisc__tp_init__1(PyNs3FqCoDelQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3FqCoDelQueueDisc_Type)
    {
        self->obj = new PyNs3FqCoDelQueueDisc__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3FqCoDelQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::FqCoDelQueueDisc();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

int _wrap_PyNs3FqCoDelQueueDisc__tp_init(PyNs3FqCoDelQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3FqCoDelQueueDisc__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3FqCoDelQueueDisc__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3FqCoDelQueueDisc_GetQuantum(PyNs3FqCoDelQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetQuantum();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelQueueDisc_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::FqCoDelQueueDisc::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3FqCoDelQueueDisc_SetQuantum(PyNs3FqCoDelQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    unsigned int quantum;
    const char *keywords[] = {"quantum", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &quantum)) {
        return NULL;
    }
    self->obj->SetQuantum(quantum);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


static PyObject*
_wrap_PyNs3FqCoDelQueueDisc__copy__(PyNs3FqCoDelQueueDisc *self)
{

    PyNs3FqCoDelQueueDisc *py_copy;
    py_copy = PyObject_GC_New(PyNs3FqCoDelQueueDisc, &PyNs3FqCoDelQueueDisc_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::FqCoDelQueueDisc(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3FqCoDelQueueDisc_methods[] = {
    {(char *) "GetQuantum", (PyCFunction) _wrap_PyNs3FqCoDelQueueDisc_GetQuantum, METH_NOARGS, "GetQuantum()\n\n" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3FqCoDelQueueDisc_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "SetQuantum", (PyCFunction) _wrap_PyNs3FqCoDelQueueDisc_SetQuantum, METH_KEYWORDS|METH_VARARGS, "SetQuantum(quantum)\n\ntype: quantum: uint32_t" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3FqCoDelQueueDisc__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3FqCoDelQueueDisc__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3FqCoDelQueueDisc__tp_clear(PyNs3FqCoDelQueueDisc *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::FqCoDelQueueDisc *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3FqCoDelQueueDisc__tp_traverse(PyNs3FqCoDelQueueDisc *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3FqCoDelQueueDisc__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3FqCoDelQueueDisc__tp_dealloc(PyNs3FqCoDelQueueDisc *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3FqCoDelQueueDisc__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3FqCoDelQueueDisc__tp_richcompare (PyNs3FqCoDelQueueDisc *PYBINDGEN_UNUSED(self), PyNs3FqCoDelQueueDisc *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3FqCoDelQueueDisc_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3FqCoDelQueueDisc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.FqCoDelQueueDisc",            /* tp_name */
    sizeof(PyNs3FqCoDelQueueDisc),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3FqCoDelQueueDisc__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "FqCoDelQueueDisc(arg0)\nFqCoDelQueueDisc()",                        /* Documentation string */
    (traverseproc)PyNs3FqCoDelQueueDisc__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3FqCoDelQueueDisc__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3FqCoDelQueueDisc__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3FqCoDelQueueDisc_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3FqCoDelQueueDisc, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3FqCoDelQueueDisc__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3PfifoFastQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PfifoFastQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PfifoFastQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_DoInitialize(PyNs3PfifoFastQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PfifoFastQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PfifoFastQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_NotifyNewAggregate(PyNs3PfifoFastQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PfifoFastQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PfifoFastQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_DoDispose(PyNs3PfifoFastQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PfifoFastQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PfifoFastQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

bool
PyNs3PfifoFastQueueDisc__PythonHelper::CheckConfig()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PfifoFastQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckConfig"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = (ns3::PfifoFastQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckConfig", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem >
PyNs3PfifoFastQueueDisc__PythonHelper::DoDequeue()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PfifoFastQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDequeue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = (ns3::PfifoFastQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDequeue", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

bool
PyNs3PfifoFastQueueDisc__PythonHelper::DoEnqueue(ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PfifoFastQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoEnqueue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = (ns3::PfifoFastQueueDisc*) this;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoEnqueue", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem const >
PyNs3PfifoFastQueueDisc__PythonHelper::DoPeek() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PfifoFastQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoPeek"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = const_cast< ns3::PfifoFastQueueDisc* >((const ns3::PfifoFastQueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoPeek", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PfifoFastQueueDisc__PythonHelper::InitializeParams()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PfifoFastQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "InitializeParams"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = (ns3::PfifoFastQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "InitializeParams", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PfifoFastQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

uint32_t
PyNs3PfifoFastQueueDisc__PythonHelper::GetQuota() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    uint32_t retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetQuota", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PfifoFastQueueDisc__PythonHelper::SetQuota(uint32_t const quota)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::SetQuota(quota);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetQuota", (char *) "N", PyLong_FromUnsignedLong(quota));
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


void
PyNs3PfifoFastQueueDisc__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3PfifoFastQueueDisc__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3PfifoFastQueueDisc__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PfifoFastQueueDisc__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3PfifoFastQueueDisc__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3PfifoFastQueueDisc__tp_init__0(PyNs3PfifoFastQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3PfifoFastQueueDisc *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3PfifoFastQueueDisc_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3PfifoFastQueueDisc_Type)
    {
        self->obj = new PyNs3PfifoFastQueueDisc__PythonHelper(*((PyNs3PfifoFastQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3PfifoFastQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::PfifoFastQueueDisc(*((PyNs3PfifoFastQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

static int
_wrap_PyNs3PfifoFastQueueDisc__tp_init__1(PyNs3PfifoFastQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3PfifoFastQueueDisc_Type)
    {
        self->obj = new PyNs3PfifoFastQueueDisc__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3PfifoFastQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::PfifoFastQueueDisc();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

int _wrap_PyNs3PfifoFastQueueDisc__tp_init(PyNs3PfifoFastQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3PfifoFastQueueDisc__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3PfifoFastQueueDisc__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3PfifoFastQueueDisc_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::PfifoFastQueueDisc::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


static PyObject*
_wrap_PyNs3PfifoFastQueueDisc__copy__(PyNs3PfifoFastQueueDisc *self)
{

    PyNs3PfifoFastQueueDisc *py_copy;
    py_copy = PyObject_GC_New(PyNs3PfifoFastQueueDisc, &PyNs3PfifoFastQueueDisc_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::PfifoFastQueueDisc(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3PfifoFastQueueDisc_methods[] = {
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3PfifoFastQueueDisc_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3PfifoFastQueueDisc__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3PfifoFastQueueDisc__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3PfifoFastQueueDisc__tp_clear(PyNs3PfifoFastQueueDisc *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::PfifoFastQueueDisc *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3PfifoFastQueueDisc__tp_traverse(PyNs3PfifoFastQueueDisc *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3PfifoFastQueueDisc__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3PfifoFastQueueDisc__tp_dealloc(PyNs3PfifoFastQueueDisc *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3PfifoFastQueueDisc__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3PfifoFastQueueDisc__tp_richcompare (PyNs3PfifoFastQueueDisc *PYBINDGEN_UNUSED(self), PyNs3PfifoFastQueueDisc *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3PfifoFastQueueDisc_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3PfifoFastQueueDisc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.PfifoFastQueueDisc",            /* tp_name */
    sizeof(PyNs3PfifoFastQueueDisc),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3PfifoFastQueueDisc__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "PfifoFastQueueDisc(arg0)\nPfifoFastQueueDisc()",                        /* Documentation string */
    (traverseproc)PyNs3PfifoFastQueueDisc__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3PfifoFastQueueDisc__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3PfifoFastQueueDisc__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3PfifoFastQueueDisc_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3PfifoFastQueueDisc, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3PfifoFastQueueDisc__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




PyObject *
PyNs3PieQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PieQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PieQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyConstructionCompleted of class ObjectBase is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyConstructionCompleted__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PieQueueDisc__PythonHelper::_wrap_DoInitialize(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PieQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PieQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoInitialize of class QueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoInitialize__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PieQueueDisc__PythonHelper::_wrap_NotifyNewAggregate(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PieQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PieQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method NotifyNewAggregate of class Object is protected and can only be called by a subclass");
        return NULL;
    }
    helper->NotifyNewAggregate__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

PyObject *
PyNs3PieQueueDisc__PythonHelper::_wrap_DoDispose(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PieQueueDisc__PythonHelper *helper = dynamic_cast< PyNs3PieQueueDisc__PythonHelper* >(self->obj);
    
    if (helper == NULL) {
        PyErr_SetString(PyExc_TypeError, "Method DoDispose of class PieQueueDisc is protected and can only be called by a subclass");
        return NULL;
    }
    helper->DoDispose__parent_caller();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

void
PyNs3PieQueueDisc__PythonHelper::DoDispose()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PieQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDispose"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::PieQueueDisc::DoDispose();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = (ns3::PieQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDispose", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

bool
PyNs3PieQueueDisc__PythonHelper::CheckConfig()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PieQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "CheckConfig"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = (ns3::PieQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "CheckConfig", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem >
PyNs3PieQueueDisc__PythonHelper::DoDequeue()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PieQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoDequeue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = (ns3::PieQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoDequeue", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

bool
PyNs3PieQueueDisc__PythonHelper::DoEnqueue(ns3::Ptr< ns3::QueueDiscItem > item)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PieQueueDisc *self_obj_before;
    PyObject *py_retval;
    bool retval;
    PyNs3QueueDiscItem *py_QueueDiscItem;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    PyObject *py_boolretval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoEnqueue"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = (ns3::PieQueueDisc*) this;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item)));
    if (wrapper_lookup_iter == PyNs3Empty_wrapper_registry.end()) {
        py_QueueDiscItem = NULL;
    } else {
        py_QueueDiscItem = (PyNs3QueueDiscItem *) wrapper_lookup_iter->second;
        Py_INCREF(py_QueueDiscItem);
    }
    
    if (py_QueueDiscItem == NULL)
    {
        wrapper_type = PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.lookup_wrapper(typeid(*const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))), &PyNs3QueueDiscItem_Type);
        py_QueueDiscItem = PyObject_New(PyNs3QueueDiscItem, wrapper_type);
    
        py_QueueDiscItem->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item))->Ref();
        py_QueueDiscItem->obj = const_cast<ns3::QueueDiscItem *> (ns3::PeekPointer (item));
        PyNs3Empty_wrapper_registry[(void *) py_QueueDiscItem->obj] = (PyObject *) py_QueueDiscItem;
    }
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoEnqueue", (char *) "N", py_QueueDiscItem);
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O", &py_boolretval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    retval = PyObject_IsTrue(py_boolretval);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

ns3::Ptr< ns3::QueueDiscItem const >
PyNs3PieQueueDisc__PythonHelper::DoPeek() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PieQueueDisc *self_obj_before;
    PyObject *py_retval;
    ns3::Ptr< ns3::QueueDiscItem const > retval;
    PyNs3QueueDiscItem *tmp_QueueDiscItem;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoPeek"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    self_obj_before = reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = const_cast< ns3::PieQueueDisc* >((const ns3::PieQueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoPeek", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDiscItem_Type, &tmp_QueueDiscItem)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
    
        PyErr_Print();
        Py_FatalError("Error detected, but parent virtual is pure virtual or private virtual, "
                      "and return is a class without trival constructor");
    }
    // dangerous!
    retval = ns3::Ptr< ns3::QueueDiscItem  > (tmp_QueueDiscItem->obj);
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PieQueueDisc__PythonHelper::InitializeParams()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::PieQueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "InitializeParams"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = (ns3::PieQueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "InitializeParams", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3PieQueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

uint32_t
PyNs3PieQueueDisc__PythonHelper::GetQuota() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    uint32_t retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = const_cast< ns3::QueueDisc* >((const ns3::QueueDisc*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetQuota", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &retval)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::QueueDisc::GetQuota();
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PieQueueDisc__PythonHelper::SetQuota(uint32_t const quota)
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "SetQuota"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::SetQuota(quota);
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "SetQuota", (char *) "N", PyLong_FromUnsignedLong(quota));
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


void
PyNs3PieQueueDisc__PythonHelper::DoInitialize()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::QueueDisc *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "DoInitialize"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::QueueDisc::DoInitialize();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj;
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = (ns3::QueueDisc*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "DoInitialize", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3QueueDisc* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

ns3::TypeId
PyNs3PieQueueDisc__PythonHelper::GetInstanceTypeId() const
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    PyNs3TypeId *tmp_TypeId;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "GetInstanceTypeId"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = const_cast< ns3::Object* >((const ns3::Object*) this);
    py_retval = PyObject_CallMethod(m_pyself, (char *) "GetInstanceTypeId", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    py_retval = Py_BuildValue((char*) "(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3TypeId_Type, &tmp_TypeId)) {
        PyErr_Print();
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return ns3::Object::GetInstanceTypeId();
    }
    ns3::TypeId retval = *tmp_TypeId->obj;
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return retval;
}

void
PyNs3PieQueueDisc__PythonHelper::NotifyNewAggregate()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::Object *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyNewAggregate"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::Object::NotifyNewAggregate();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3Object* >(m_pyself)->obj;
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = (ns3::Object*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyNewAggregate", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3Object* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}

void
PyNs3PieQueueDisc__PythonHelper::NotifyConstructionCompleted()
{
    PyGILState_STATE __py_gil_state;
    PyObject *py_method;
    ns3::ObjectBase *self_obj_before;
    PyObject *py_retval;
    
    __py_gil_state = (PyEval_ThreadsInitialized() ? PyGILState_Ensure() : (PyGILState_STATE) 0);
    py_method = PyObject_GetAttrString(m_pyself, (char *) "NotifyConstructionCompleted"); PyErr_Clear();
    if (py_method == NULL || Py_TYPE(py_method) == &PyCFunction_Type) {
        ns3::ObjectBase::NotifyConstructionCompleted();
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    self_obj_before = reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj;
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = (ns3::ObjectBase*) this;
    py_retval = PyObject_CallMethod(m_pyself, (char *) "NotifyConstructionCompleted", (char *) "");
    if (py_retval == NULL) {
        PyErr_Print();
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "function/method should return None");
        Py_DECREF(py_retval);
        reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
        Py_XDECREF(py_method);
        if (PyEval_ThreadsInitialized())
            PyGILState_Release(__py_gil_state);
        return;
    }
    Py_DECREF(py_retval);
    reinterpret_cast< PyNs3ObjectBase* >(m_pyself)->obj = self_obj_before;
    Py_XDECREF(py_method);
    if (PyEval_ThreadsInitialized())
        PyGILState_Release(__py_gil_state);
    return;
}


static int
_wrap_PyNs3PieQueueDisc__tp_init__0(PyNs3PieQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3PieQueueDisc *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3PieQueueDisc_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3PieQueueDisc_Type)
    {
        self->obj = new PyNs3PieQueueDisc__PythonHelper(*((PyNs3PieQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3PieQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::PieQueueDisc(*((PyNs3PieQueueDisc *) arg0)->obj);
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

static int
_wrap_PyNs3PieQueueDisc__tp_init__1(PyNs3PieQueueDisc *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    if (Py_TYPE(self) != &PyNs3PieQueueDisc_Type)
    {
        self->obj = new PyNs3PieQueueDisc__PythonHelper();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ((PyNs3PieQueueDisc__PythonHelper*) self->obj)->set_pyobj((PyObject *)self);
        ns3::CompleteConstruct(self->obj);
    } else {
        // visibility: 'public'
        self->obj = new ns3::PieQueueDisc();
        self->obj->Ref ();
        self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
        ns3::CompleteConstruct(self->obj);
    }
    return 0;
}

int _wrap_PyNs3PieQueueDisc__tp_init(PyNs3PieQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3PieQueueDisc__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3PieQueueDisc__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


PyObject *
_wrap_PyNs3PieQueueDisc_GetMode(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    ns3::Queue::QueueMode retval;
    
    retval = self->obj->GetMode();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_SetQueueLimit(PyNs3PieQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    unsigned int lim;
    const char *keywords[] = {"lim", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &lim)) {
        return NULL;
    }
    self->obj->SetQueueLimit(lim);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_GetTypeId(void)
{
    PyObject *py_retval;
    PyNs3TypeId *py_TypeId;
    
    ns3::TypeId retval = ns3::PieQueueDisc::GetTypeId();
    py_TypeId = PyObject_New(PyNs3TypeId, &PyNs3TypeId_Type);
    py_TypeId->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_TypeId->obj = new ns3::TypeId(retval);
    PyNs3TypeId_wrapper_registry[(void *) py_TypeId->obj] = (PyObject *) py_TypeId;
    py_retval = Py_BuildValue((char *) "N", py_TypeId);
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_GetStats(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3PieQueueDiscStats *py_Stats;
    
    ns3::PieQueueDisc::Stats retval = self->obj->GetStats();
    py_Stats = PyObject_New(PyNs3PieQueueDiscStats, &PyNs3PieQueueDiscStats_Type);
    py_Stats->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Stats->obj = new ns3::PieQueueDisc::Stats(retval);
    PyNs3PieQueueDiscStats_wrapper_registry[(void *) py_Stats->obj] = (PyObject *) py_Stats;
    py_retval = Py_BuildValue((char *) "N", py_Stats);
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_SetMode(PyNs3PieQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    ns3::Queue::QueueMode mode;
    const char *keywords[] = {"mode", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &mode)) {
        return NULL;
    }
    self->obj->SetMode(mode);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_AssignStreams(PyNs3PieQueueDisc *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int64_t retval;
    int64_t stream;
    const char *keywords[] = {"stream", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "L", (char **) keywords, &stream)) {
        return NULL;
    }
    retval = self->obj->AssignStreams(stream);
    py_retval = Py_BuildValue((char *) "L", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_GetQueueDelay(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    PyNs3Time *py_Time;
    
    ns3::Time retval = self->obj->GetQueueDelay();
    py_Time = PyObject_New(PyNs3Time, &PyNs3Time_Type);
    py_Time->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Time->obj = new ns3::Time(retval);
    PyNs3Time_wrapper_registry[(void *) py_Time->obj] = (PyObject *) py_Time;
    py_retval = Py_BuildValue((char *) "N", py_Time);
    return py_retval;
}


PyObject *
_wrap_PyNs3PieQueueDisc_GetQueueSize(PyNs3PieQueueDisc *self)
{
    PyObject *py_retval;
    uint32_t retval;
    
    retval = self->obj->GetQueueSize();
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


static PyObject*
_wrap_PyNs3PieQueueDisc__copy__(PyNs3PieQueueDisc *self)
{

    PyNs3PieQueueDisc *py_copy;
    py_copy = PyObject_GC_New(PyNs3PieQueueDisc, &PyNs3PieQueueDisc_Type);
    py_copy->inst_dict = NULL;
    
    py_copy->obj = new ns3::PieQueueDisc(*self->obj);
    py_copy->inst_dict = NULL;
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3ObjectBase_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3PieQueueDisc_methods[] = {
    {(char *) "GetMode", (PyCFunction) _wrap_PyNs3PieQueueDisc_GetMode, METH_NOARGS, "GetMode()\n\n" },
    {(char *) "SetQueueLimit", (PyCFunction) _wrap_PyNs3PieQueueDisc_SetQueueLimit, METH_KEYWORDS|METH_VARARGS, "SetQueueLimit(lim)\n\ntype: lim: uint32_t" },
    {(char *) "GetTypeId", (PyCFunction) _wrap_PyNs3PieQueueDisc_GetTypeId, METH_NOARGS|METH_STATIC, "GetTypeId()\n\n" },
    {(char *) "GetStats", (PyCFunction) _wrap_PyNs3PieQueueDisc_GetStats, METH_NOARGS, "GetStats()\n\n" },
    {(char *) "SetMode", (PyCFunction) _wrap_PyNs3PieQueueDisc_SetMode, METH_KEYWORDS|METH_VARARGS, "SetMode(mode)\n\ntype: mode: ns3::Queue::QueueMode" },
    {(char *) "AssignStreams", (PyCFunction) _wrap_PyNs3PieQueueDisc_AssignStreams, METH_KEYWORDS|METH_VARARGS, "AssignStreams(stream)\n\ntype: stream: int64_t" },
    {(char *) "GetQueueDelay", (PyCFunction) _wrap_PyNs3PieQueueDisc_GetQueueDelay, METH_NOARGS, "GetQueueDelay()\n\n" },
    {(char *) "GetQueueSize", (PyCFunction) _wrap_PyNs3PieQueueDisc_GetQueueSize, METH_NOARGS, "GetQueueSize()\n\n" },
    {(char *) "NotifyConstructionCompleted", (PyCFunction) PyNs3PieQueueDisc__PythonHelper::_wrap_NotifyConstructionCompleted, METH_NOARGS, NULL },
    {(char *) "DoInitialize", (PyCFunction) PyNs3PieQueueDisc__PythonHelper::_wrap_DoInitialize, METH_NOARGS, NULL },
    {(char *) "NotifyNewAggregate", (PyCFunction) PyNs3PieQueueDisc__PythonHelper::_wrap_NotifyNewAggregate, METH_NOARGS, NULL },
    {(char *) "DoDispose", (PyCFunction) PyNs3PieQueueDisc__PythonHelper::_wrap_DoDispose, METH_NOARGS, NULL },
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3PieQueueDisc__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
PyNs3PieQueueDisc__tp_clear(PyNs3PieQueueDisc *self)
{
    Py_CLEAR(self->inst_dict);
    if (self->obj) {
    ns3::PieQueueDisc *tmp = self->obj;
    self->obj = NULL;
    tmp->Unref();
}
}


static int
PyNs3PieQueueDisc__tp_traverse(PyNs3PieQueueDisc *self, visitproc visit, void *arg)
{
    Py_VISIT(self->inst_dict);
    
    if (self->obj && typeid(*self->obj).name() == typeid(PyNs3PieQueueDisc__PythonHelper).name()  && self->obj->GetReferenceCount() == 1)
        Py_VISIT((PyObject *) self);

    return 0;
}


static void
_wrap_PyNs3PieQueueDisc__tp_dealloc(PyNs3PieQueueDisc *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3ObjectBase_wrapper_registry.end()) {
        PyNs3ObjectBase_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    PyNs3PieQueueDisc__tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3PieQueueDisc__tp_richcompare (PyNs3PieQueueDisc *PYBINDGEN_UNUSED(self), PyNs3PieQueueDisc *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3PieQueueDisc_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3PieQueueDisc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.PieQueueDisc",            /* tp_name */
    sizeof(PyNs3PieQueueDisc),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3PieQueueDisc__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    "PieQueueDisc(arg0)\nPieQueueDisc()",                        /* Documentation string */
    (traverseproc)PyNs3PieQueueDisc__tp_traverse,     /* tp_traverse */
    (inquiry)PyNs3PieQueueDisc__tp_clear,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3PieQueueDisc__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3PieQueueDisc_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    offsetof(PyNs3PieQueueDisc, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3PieQueueDisc__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};



std::map<void*, PyObject*> PyNs3PieQueueDiscStats_wrapper_registry;
static PyObject* _wrap_PyNs3PieQueueDiscStats__get_forcedDrop(PyNs3PieQueueDiscStats *self, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(self->obj->forcedDrop));
    return py_retval;
}
static int _wrap_PyNs3PieQueueDiscStats__set_forcedDrop(PyNs3PieQueueDiscStats *self, PyObject *value, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &self->obj->forcedDrop)) {
        Py_DECREF(py_retval);
        return -1;
    }
    Py_DECREF(py_retval);
    return 0;
}
static PyObject* _wrap_PyNs3PieQueueDiscStats__get_unforcedDrop(PyNs3PieQueueDiscStats *self, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(self->obj->unforcedDrop));
    return py_retval;
}
static int _wrap_PyNs3PieQueueDiscStats__set_unforcedDrop(PyNs3PieQueueDiscStats *self, PyObject *value, void * PYBINDGEN_UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &self->obj->unforcedDrop)) {
        Py_DECREF(py_retval);
        return -1;
    }
    Py_DECREF(py_retval);
    return 0;
}
static PyGetSetDef PyNs3PieQueueDiscStats__getsets[] = {
    {
        (char*) "unforcedDrop", /* attribute name */
        (getter) _wrap_PyNs3PieQueueDiscStats__get_unforcedDrop, /* C function to get the attribute */
        (setter) _wrap_PyNs3PieQueueDiscStats__set_unforcedDrop, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "forcedDrop", /* attribute name */
        (getter) _wrap_PyNs3PieQueueDiscStats__get_forcedDrop, /* C function to get the attribute */
        (setter) _wrap_PyNs3PieQueueDiscStats__set_forcedDrop, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};


static int
_wrap_PyNs3PieQueueDiscStats__tp_init__0(PyNs3PieQueueDiscStats *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::PieQueueDisc::Stats();
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

static int
_wrap_PyNs3PieQueueDiscStats__tp_init__1(PyNs3PieQueueDiscStats *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyNs3PieQueueDiscStats *arg0;
    const char *keywords[] = {"arg0", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyNs3PieQueueDiscStats_Type, &arg0)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return -1;
    }
    self->obj = new ns3::PieQueueDisc::Stats(*((PyNs3PieQueueDiscStats *) arg0)->obj);
    self->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    return 0;
}

int _wrap_PyNs3PieQueueDiscStats__tp_init(PyNs3PieQueueDiscStats *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};
    retval = _wrap_PyNs3PieQueueDiscStats__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }
    retval = _wrap_PyNs3PieQueueDiscStats__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }
    error_list = PyList_New(2);
    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);
    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);
    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);
    return -1;
}


static PyObject*
_wrap_PyNs3PieQueueDiscStats__copy__(PyNs3PieQueueDiscStats *self)
{

    PyNs3PieQueueDiscStats *py_copy;
    py_copy = PyObject_New(PyNs3PieQueueDiscStats, &PyNs3PieQueueDiscStats_Type);
    py_copy->obj = new ns3::PieQueueDisc::Stats(*self->obj);
    py_copy->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    PyNs3PieQueueDiscStats_wrapper_registry[(void *) py_copy->obj] = (PyObject *) py_copy;
    return (PyObject*) py_copy;
}

static PyMethodDef PyNs3PieQueueDiscStats_methods[] = {
    {(char *) "__copy__", (PyCFunction) _wrap_PyNs3PieQueueDiscStats__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static void
_wrap_PyNs3PieQueueDiscStats__tp_dealloc(PyNs3PieQueueDiscStats *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3PieQueueDiscStats_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3PieQueueDiscStats_wrapper_registry.end()) {
        PyNs3PieQueueDiscStats_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
        ns3::PieQueueDisc::Stats *tmp = self->obj;
        self->obj = NULL;
        if (!(self->flags&PYBINDGEN_WRAPPER_FLAG_OBJECT_NOT_OWNED)) {
            delete tmp;
        }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3PieQueueDiscStats__tp_richcompare (PyNs3PieQueueDiscStats *PYBINDGEN_UNUSED(self), PyNs3PieQueueDiscStats *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3PieQueueDiscStats_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3PieQueueDiscStats_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.PieQueueDisc.Stats",            /* tp_name */
    sizeof(PyNs3PieQueueDiscStats),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3PieQueueDiscStats__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    "Stats(arg0)\nStats()",                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3PieQueueDiscStats__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3PieQueueDiscStats_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    PyNs3PieQueueDiscStats__getsets,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3PieQueueDiscStats__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




static int
_wrap_PyNs3QueueDiscItem__tp_init(void)
{
    PyErr_SetString(PyExc_TypeError, "class 'QueueDiscItem' cannot be constructed (have pure virtual methods but no helper class)");
    return -1;
}


PyObject *
_wrap_PyNs3QueueDiscItem_GetTxQueueIndex(PyNs3QueueDiscItem *self)
{
    PyObject *py_retval;
    uint8_t retval;
    
    retval = self->obj->GetTxQueueIndex();
    py_retval = Py_BuildValue((char *) "i", (int)retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscItem_GetProtocol(PyNs3QueueDiscItem *self)
{
    PyObject *py_retval;
    uint16_t retval;
    
    retval = self->obj->GetProtocol();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscItem_SetTxQueueIndex(PyNs3QueueDiscItem *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    int txq;
    const char *keywords[] = {"txq", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &txq)) {
        return NULL;
    }
    if (txq > 0xff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return NULL;
    }
    self->obj->SetTxQueueIndex(txq);
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscItem_GetAddress(PyNs3QueueDiscItem *self)
{
    PyObject *py_retval;
    PyNs3Address *py_Address;
    
    ns3::Address retval = self->obj->GetAddress();
    py_Address = PyObject_New(PyNs3Address, &PyNs3Address_Type);
    py_Address->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
    py_Address->obj = new ns3::Address(retval);
    PyNs3Address_wrapper_registry[(void *) py_Address->obj] = (PyObject *) py_Address;
    py_retval = Py_BuildValue((char *) "N", py_Address);
    return py_retval;
}


PyObject *
_wrap_PyNs3QueueDiscItem_AddHeader(PyNs3QueueDiscItem *self)
{
    PyObject *py_retval;
    
    self->obj->AddHeader();
    Py_INCREF(Py_None);
    py_retval = Py_None;
    return py_retval;
}

static PyMethodDef PyNs3QueueDiscItem_methods[] = {
    {(char *) "GetTxQueueIndex", (PyCFunction) _wrap_PyNs3QueueDiscItem_GetTxQueueIndex, METH_NOARGS, "GetTxQueueIndex()\n\n" },
    {(char *) "GetProtocol", (PyCFunction) _wrap_PyNs3QueueDiscItem_GetProtocol, METH_NOARGS, "GetProtocol()\n\n" },
    {(char *) "SetTxQueueIndex", (PyCFunction) _wrap_PyNs3QueueDiscItem_SetTxQueueIndex, METH_KEYWORDS|METH_VARARGS, "SetTxQueueIndex(txq)\n\ntype: txq: uint8_t" },
    {(char *) "GetAddress", (PyCFunction) _wrap_PyNs3QueueDiscItem_GetAddress, METH_NOARGS, "GetAddress()\n\n" },
    {(char *) "AddHeader", (PyCFunction) _wrap_PyNs3QueueDiscItem_AddHeader, METH_NOARGS, "AddHeader()\n\n" },
    {NULL, NULL, 0, NULL}
};

static void
_wrap_PyNs3QueueDiscItem__tp_dealloc(PyNs3QueueDiscItem *self)
{
    std::map<void*, PyObject*>::iterator wrapper_lookup_iter;
    wrapper_lookup_iter = PyNs3Empty_wrapper_registry.find((void *) self->obj);
    if (wrapper_lookup_iter != PyNs3Empty_wrapper_registry.end()) {
        PyNs3Empty_wrapper_registry.erase(wrapper_lookup_iter);
    }
    
    if (self->obj) {
        ns3::QueueDiscItem *tmp = self->obj;
        self->obj = NULL;
        tmp->Unref();
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
_wrap_PyNs3QueueDiscItem__tp_richcompare (PyNs3QueueDiscItem *PYBINDGEN_UNUSED(self), PyNs3QueueDiscItem *other, int opid)
{
    
    if (!PyObject_IsInstance((PyObject*) other, (PyObject*) &PyNs3QueueDiscItem_Type)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    switch (opid)
    {
    case Py_LT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_LE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_EQ:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_NE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GE:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    case Py_GT:
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    } /* closes switch (opid) */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

PyTypeObject PyNs3QueueDiscItem_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.QueueDiscItem",            /* tp_name */
    sizeof(PyNs3QueueDiscItem),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_PyNs3QueueDiscItem__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    "QueueDiscItem(p, addr, protocol)",                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)_wrap_PyNs3QueueDiscItem__tp_richcompare,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)NULL,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)PyNs3QueueDiscItem_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    0,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_PyNs3QueueDiscItem__tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};


/* --- containers --- */



static void
Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_clear(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter *self)
{
    Py_CLEAR(self->container);
    delete self->iterator;
    self->iterator = NULL;

}


static int
Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_traverse(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter *self, visitproc visit, void *arg)
{
    Py_VISIT((PyObject *) self->container);
    return 0;
}


static void
_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt____tp_dealloc(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__ *self)
{
    delete self->obj;
    self->obj = NULL;

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static void
_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_dealloc(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter *self)
{
    Py_CLEAR(self->container);
    delete self->iterator;
    self->iterator = NULL;

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject*
_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt____tp_iter(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__ *self)
{
    Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter *iter = PyObject_GC_New(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter, &Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter_Type);
    Py_INCREF(self);
    iter->container = self;
    iter->iterator = new std::vector< ns3::Ptr< ns3::QueueDisc > >::iterator(self->obj->begin());
    return (PyObject*) iter;
}


static PyObject*
_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_iter(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter *self)
{
    Py_INCREF(self);
    return (PyObject*) self;
}

static PyObject* _wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_iternext(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter *self)
{
    PyObject *py_retval;
    std::vector< ns3::Ptr< ns3::QueueDisc > >::iterator iter;
    PyNs3QueueDisc *py_QueueDisc;
    std::map<void*, PyObject*>::const_iterator wrapper_lookup_iter;
    PyTypeObject *wrapper_type = 0;
    
    iter = *self->iterator;
    if (iter == self->container->obj->end()) {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
    ++(*self->iterator);
    if (!(const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter))))) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    if (typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter))))).name() == typeid(PyNs3QueueDisc__PythonHelper).name())
    {
        py_QueueDisc = reinterpret_cast< PyNs3QueueDisc* >(reinterpret_cast< PyNs3QueueDisc__PythonHelper* >(const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter))))->m_pyself);
        py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter)));
        Py_INCREF(py_QueueDisc);
    } else {
        wrapper_lookup_iter = PyNs3ObjectBase_wrapper_registry.find((void *) const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter))));
        if (wrapper_lookup_iter == PyNs3ObjectBase_wrapper_registry.end()) {
            py_QueueDisc = NULL;
        } else {
            py_QueueDisc = (PyNs3QueueDisc *) wrapper_lookup_iter->second;
            Py_INCREF(py_QueueDisc);
        }
    
        if (py_QueueDisc == NULL) {
            wrapper_type = PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.lookup_wrapper(typeid((*const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter))))), &PyNs3QueueDisc_Type);
            py_QueueDisc = PyObject_GC_New(PyNs3QueueDisc, wrapper_type);
            py_QueueDisc->inst_dict = NULL;
    
            py_QueueDisc->inst_dict = NULL;
            py_QueueDisc->flags = PYBINDGEN_WRAPPER_FLAG_NONE;
            const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter)))->Ref();
            py_QueueDisc->obj = const_cast<ns3::QueueDisc *> (ns3::PeekPointer ((*iter)));
            PyNs3ObjectBase_wrapper_registry[(void *) py_QueueDisc->obj] = (PyObject *) py_QueueDisc;
        }
    }
    py_retval = Py_BuildValue((char *) "N", py_QueueDisc);
    return py_retval;
}

int _wrap_convert_py2c__ns3__Ptr__lt___ns3__QueueDisc___gt__(PyObject *value, ns3::Ptr< ns3::QueueDisc > *address)
{
    PyObject *py_retval;
    PyNs3QueueDisc *tmp_QueueDisc;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyNs3QueueDisc_Type, &tmp_QueueDisc)) {
        Py_DECREF(py_retval);
        return 0;
    }
    // dangerous!
    *address = ns3::Ptr< ns3::QueueDisc  > (tmp_QueueDisc->obj);
    Py_DECREF(py_retval);
    return 1;
}


int _wrap_convert_py2c__std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__(PyObject *arg, std::vector< ns3::Ptr< ns3::QueueDisc > > *container)
{
    if (PyObject_IsInstance(arg, (PyObject*) &Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt___Type)) {
        *container = *((Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__*)arg)->obj;
    } else if (PyList_Check(arg)) {
        container->clear();
        Py_ssize_t size = PyList_Size(arg);
        for (Py_ssize_t i = 0; i < size; i++) {
            ns3::Ptr< ns3::QueueDisc > item;
            if (!_wrap_convert_py2c__ns3__Ptr__lt___ns3__QueueDisc___gt__(PyList_GET_ITEM(arg, i), &item)) {
                return 0;
            }
            container->push_back(item);
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "parameter must be None, a Std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__ instance, or a list of ns3::Ptr< ns3::QueueDisc >");
        return 0;
    }
    return 1;
}


static int
_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt____tp_init(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__ *self, PyObject *args, PyObject *kwargs)
{
    const char *keywords[] = {"arg", NULL};
    PyObject *arg = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "|O", (char **) keywords, &arg)) {
        return -1;
    }

    self->obj = new std::vector< ns3::Ptr< ns3::QueueDisc > >;

    if (arg == NULL)
        return 0;

    if (!_wrap_convert_py2c__std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__(arg, self->obj)) {
        delete self->obj;
        self->obj = NULL;
        return -1;
    }
    return 0;
}

PyTypeObject Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt___Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.Std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__",            /* tp_name */
    sizeof(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt____tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)NULL,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt____tp_iter,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    NULL,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt____tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};

PyTypeObject Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.Std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter",            /* tp_name */
    sizeof(Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_traverse,     /* tp_traverse */
    (inquiry)Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_clear,             /* tp_clear */
    (richcmpfunc)NULL,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_iter,          /* tp_iter */
    (iternextfunc)_wrap_Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter__tp_iternext,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    NULL,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)NULL,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};




static void
Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_clear(Pystd__vector__lt___short_unsigned_int___gt__Iter *self)
{
    Py_CLEAR(self->container);
    delete self->iterator;
    self->iterator = NULL;

}


static int
Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_traverse(Pystd__vector__lt___short_unsigned_int___gt__Iter *self, visitproc visit, void *arg)
{
    Py_VISIT((PyObject *) self->container);
    return 0;
}


static void
_wrap_Pystd__vector__lt___short_unsigned_int___gt____tp_dealloc(Pystd__vector__lt___short_unsigned_int___gt__ *self)
{
    delete self->obj;
    self->obj = NULL;

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static void
_wrap_Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_dealloc(Pystd__vector__lt___short_unsigned_int___gt__Iter *self)
{
    Py_CLEAR(self->container);
    delete self->iterator;
    self->iterator = NULL;

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject*
_wrap_Pystd__vector__lt___short_unsigned_int___gt____tp_iter(Pystd__vector__lt___short_unsigned_int___gt__ *self)
{
    Pystd__vector__lt___short_unsigned_int___gt__Iter *iter = PyObject_GC_New(Pystd__vector__lt___short_unsigned_int___gt__Iter, &Pystd__vector__lt___short_unsigned_int___gt__Iter_Type);
    Py_INCREF(self);
    iter->container = self;
    iter->iterator = new std::vector< short unsigned int >::iterator(self->obj->begin());
    return (PyObject*) iter;
}


static PyObject*
_wrap_Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_iter(Pystd__vector__lt___short_unsigned_int___gt__Iter *self)
{
    Py_INCREF(self);
    return (PyObject*) self;
}

static PyObject* _wrap_Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_iternext(Pystd__vector__lt___short_unsigned_int___gt__Iter *self)
{
    PyObject *py_retval;
    std::vector< short unsigned int >::iterator iter;
    
    iter = *self->iterator;
    if (iter == self->container->obj->end()) {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
    ++(*self->iterator);
    py_retval = Py_BuildValue((char *) "i", (*iter));
    return py_retval;
}

int _wrap_convert_py2c__short_unsigned_int(PyObject *value, short unsigned int *address)
{
    PyObject *py_retval;
    int tmp;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "i", &tmp)) {
        Py_DECREF(py_retval);
        return 0;
    }
    if (tmp > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        Py_DECREF(py_retval);
        return 0;
    }
    *address = tmp;
    Py_DECREF(py_retval);
    return 1;
}


int _wrap_convert_py2c__std__vector__lt___short_unsigned_int___gt__(PyObject *arg, std::vector< short unsigned int > *container)
{
    if (PyObject_IsInstance(arg, (PyObject*) &Pystd__vector__lt___short_unsigned_int___gt___Type)) {
        *container = *((Pystd__vector__lt___short_unsigned_int___gt__*)arg)->obj;
    } else if (PyList_Check(arg)) {
        container->clear();
        Py_ssize_t size = PyList_Size(arg);
        for (Py_ssize_t i = 0; i < size; i++) {
            short unsigned int item;
            if (!_wrap_convert_py2c__short_unsigned_int(PyList_GET_ITEM(arg, i), &item)) {
                return 0;
            }
            container->push_back(item);
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "parameter must be None, a Std__vector__lt___short_unsigned_int___gt__ instance, or a list of short unsigned int");
        return 0;
    }
    return 1;
}


static int
_wrap_Pystd__vector__lt___short_unsigned_int___gt____tp_init(Pystd__vector__lt___short_unsigned_int___gt__ *self, PyObject *args, PyObject *kwargs)
{
    const char *keywords[] = {"arg", NULL};
    PyObject *arg = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "|O", (char **) keywords, &arg)) {
        return -1;
    }

    self->obj = new std::vector< short unsigned int >;

    if (arg == NULL)
        return 0;

    if (!_wrap_convert_py2c__std__vector__lt___short_unsigned_int___gt__(arg, self->obj)) {
        delete self->obj;
        self->obj = NULL;
        return -1;
    }
    return 0;
}

PyTypeObject Pystd__vector__lt___short_unsigned_int___gt___Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.Std__vector__lt___short_unsigned_int___gt__",            /* tp_name */
    sizeof(Pystd__vector__lt___short_unsigned_int___gt__),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_Pystd__vector__lt___short_unsigned_int___gt____tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)NULL,     /* tp_traverse */
    (inquiry)NULL,             /* tp_clear */
    (richcmpfunc)NULL,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)_wrap_Pystd__vector__lt___short_unsigned_int___gt____tp_iter,          /* tp_iter */
    (iternextfunc)NULL,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    NULL,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_Pystd__vector__lt___short_unsigned_int___gt____tp_init,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};

PyTypeObject Pystd__vector__lt___short_unsigned_int___gt__Iter_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "traffic_control.Std__vector__lt___short_unsigned_int___gt__Iter",            /* tp_name */
    sizeof(Pystd__vector__lt___short_unsigned_int___gt__Iter),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)_wrap_Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_dealloc,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)NULL,       /* tp_getattr */
    (setattrfunc)NULL,       /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL, 
#else
    (cmpfunc)NULL,           /* tp_compare */
#endif
    (reprfunc)NULL,             /* tp_repr */
    (PyNumberMethods*)NULL,     /* tp_as_number */
    (PySequenceMethods*)NULL, /* tp_as_sequence */
    (PyMappingMethods*)NULL,   /* tp_as_mapping */
    (hashfunc)NULL,             /* tp_hash */
    (ternaryfunc)NULL,          /* tp_call */
    (reprfunc)NULL,              /* tp_str */
    (getattrofunc)NULL,     /* tp_getattro */
    (setattrofunc)NULL,     /* tp_setattro */
    (PyBufferProcs*)NULL,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_traverse,     /* tp_traverse */
    (inquiry)Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_clear,             /* tp_clear */
    (richcmpfunc)NULL,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)_wrap_Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_iter,          /* tp_iter */
    (iternextfunc)_wrap_Pystd__vector__lt___short_unsigned_int___gt__Iter__tp_iternext,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    NULL,                     /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)NULL,    /* tp_descr_get */
    (descrsetfunc)NULL,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)NULL,             /* tp_init */
    (allocfunc)PyType_GenericAlloc,           /* tp_alloc */
    (newfunc)PyType_GenericNew,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)NULL,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    (destructor) NULL                  /* tp_del */
};


/* --- enumerations --- */

















































#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef traffic_control_moduledef = {
    PyModuleDef_HEAD_INIT,
    "traffic_control",
    NULL,
    -1,
    traffic_control_functions,
};
#endif


#if PY_VERSION_HEX >= 0x03000000
    #define MOD_ERROR NULL
    #define MOD_INIT(name) PyObject* PyInit_##name(void)
    #define MOD_RETURN(val) val
#else
    #define MOD_ERROR
    #define MOD_INIT(name) void init##name(void)
    #define MOD_RETURN(val)
#endif
#if defined(__cplusplus)
extern "C"
#endif
#if defined(__GNUC__) && __GNUC__ >= 4
__attribute__ ((visibility("default")))
#endif


MOD_INIT(traffic_control)
{
    PyObject *m;
    PyObject *submodule;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&traffic_control_moduledef);
    #else
    m = Py_InitModule3((char *) "traffic_control", traffic_control_functions, NULL);
    #endif
    if (m == NULL) {
        return MOD_ERROR;
    }
    PyModule_AddIntConstant(m, (char *) "STD_IOS_IN", std::ios::in);
    PyModule_AddIntConstant(m, (char *) "STD_IOS_OUT", std::ios::out);
    PyModule_AddIntConstant(m, (char *) "STD_IOS_ATE", std::ios::ate);
    PyModule_AddIntConstant(m, (char *) "STD_IOS_APP", std::ios::app);
    PyModule_AddIntConstant(m, (char *) "STD_IOS_TRUNC", std::ios::trunc);
    PyModule_AddIntConstant(m, (char *) "STD_IOS_BINARY", std::ios::binary);
    /* Import the 'ns3::Address' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Address_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Address");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Address_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Address_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Address_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::AttributeConstructionList' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AttributeConstructionList_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AttributeConstructionList");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3AttributeConstructionList_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3AttributeConstructionList_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3AttributeConstructionList_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::AttributeConstructionList::Item' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AttributeConstructionListItem_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Item");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3AttributeConstructionListItem_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3AttributeConstructionListItem_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3AttributeConstructionListItem_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Buffer' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Buffer_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Buffer");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Buffer_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Buffer_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Buffer_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Buffer::Iterator' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3BufferIterator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Iterator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3BufferIterator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3BufferIterator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3BufferIterator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ByteTagIterator' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ByteTagIterator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ByteTagIterator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ByteTagIterator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ByteTagIterator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ByteTagIterator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ByteTagIterator::Item' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ByteTagIteratorItem_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Item");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ByteTagIteratorItem_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ByteTagIteratorItem_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ByteTagIteratorItem_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ByteTagList' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ByteTagList_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ByteTagList");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ByteTagList_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ByteTagList_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ByteTagList_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ByteTagList::Iterator' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ByteTagListIterator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Iterator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ByteTagListIterator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ByteTagListIterator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ByteTagListIterator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ByteTagList::Iterator::Item' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ByteTagListIteratorItem_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Item");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ByteTagListIteratorItem_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ByteTagListIteratorItem_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ByteTagListIteratorItem_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::CallbackBase' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3CallbackBase_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "CallbackBase");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3CallbackBase_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3CallbackBase_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3CallbackBase_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::DataRate' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3DataRate_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "DataRate");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3DataRate_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3DataRate_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3DataRate_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::EventId' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EventId_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EventId");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3EventId_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3EventId_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3EventId_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Hasher' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Hasher_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Hasher");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Hasher_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Hasher_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Hasher_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 0 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__0_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__0");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__0_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__0_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__0_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 1 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__1_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__1");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__1_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__1_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__1_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 2 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__2_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__2");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__2_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__2_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__2_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 3 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__3_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__3");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__3_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__3_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__3_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 4 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__4_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__4");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__4_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__4_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__4_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 5 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__5_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__5");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__5_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__5_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__5_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::IntToType< 6 >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntToType__6_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntToType__6");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3IntToType__6_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3IntToType__6_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3IntToType__6_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Ipv4Address' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv4Address_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv4Address");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Ipv4Address_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Ipv4Address_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Ipv4Address_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Ipv4Mask' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv4Mask_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv4Mask");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Ipv4Mask_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Ipv4Mask_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Ipv4Mask_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Ipv6Address' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv6Address_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv6Address");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Ipv6Address_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Ipv6Address_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Ipv6Address_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Ipv6Prefix' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv6Prefix_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv6Prefix");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Ipv6Prefix_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Ipv6Prefix_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Ipv6Prefix_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Mac48Address' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Mac48Address_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Mac48Address");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Mac48Address_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Mac48Address_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Mac48Address_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::NetDeviceContainer' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3NetDeviceContainer_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "NetDeviceContainer");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3NetDeviceContainer_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3NetDeviceContainer_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3NetDeviceContainer_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ObjectBase' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ObjectBase_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ObjectBase");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ObjectBase_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ObjectBase_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ObjectBase_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ObjectDeleter' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ObjectDeleter_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ObjectDeleter");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ObjectDeleter_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ObjectDeleter_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ObjectDeleter_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::ObjectFactory' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ObjectFactory_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ObjectFactory");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ObjectFactory_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ObjectFactory_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ObjectFactory_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketMetadata' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketMetadata_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "PacketMetadata");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketMetadata_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketMetadata_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketMetadata_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketMetadata::Item' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketMetadataItem_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Item");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketMetadataItem_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketMetadataItem_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketMetadataItem_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketMetadata::ItemIterator' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketMetadataItemIterator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ItemIterator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketMetadataItemIterator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketMetadataItemIterator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketMetadataItemIterator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketTagIterator' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketTagIterator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "PacketTagIterator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketTagIterator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketTagIterator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketTagIterator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketTagIterator::Item' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketTagIteratorItem_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Item");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketTagIteratorItem_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketTagIteratorItem_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketTagIteratorItem_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketTagList' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketTagList_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "PacketTagList");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketTagList_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketTagList_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketTagList_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::PacketTagList::TagData' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3PacketTagListTagData_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TagData");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3PacketTagListTagData_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3PacketTagListTagData_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3PacketTagListTagData_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Simulator' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Simulator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Simulator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Simulator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Simulator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Simulator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Tag' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Tag_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Tag");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::TagBuffer' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TagBuffer_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TagBuffer");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TagBuffer_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TagBuffer_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TagBuffer_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TimeWithUnit' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TimeWithUnit_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TimeWithUnit");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TimeWithUnit_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TimeWithUnit_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TimeWithUnit_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Timer' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Timer_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Timer");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Timer_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Timer_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Timer_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TimerImpl' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TimerImpl_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TimerImpl");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TimerImpl_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TimerImpl_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TimerImpl_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TracedValue< bool >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TracedValue__Bool_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TracedValue__Bool");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TracedValue__Bool_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TracedValue__Bool_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TracedValue__Bool_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TracedValue< unsigned int >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TracedValue__Unsigned_int_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TracedValue__Unsigned_int");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TracedValue__Unsigned_int_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TracedValue__Unsigned_int_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TracedValue__Unsigned_int_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TypeId' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TypeId_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TypeId");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TypeId_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TypeId_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TypeId_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TypeId::AttributeInformation' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TypeIdAttributeInformation_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AttributeInformation");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TypeIdAttributeInformation_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TypeIdAttributeInformation_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TypeIdAttributeInformation_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TypeId::TraceSourceInformation' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TypeIdTraceSourceInformation_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TraceSourceInformation");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TypeIdTraceSourceInformation_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TypeIdTraceSourceInformation_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TypeIdTraceSourceInformation_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::empty' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Empty_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "empty");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Empty_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Empty_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Empty_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::int64x64_t' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Int64x64_t_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "int64x64_t");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Int64x64_t_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Int64x64_t_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Int64x64_t_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Chunk' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Chunk_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Chunk");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Header' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Header_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Header");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Object' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Object_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Object");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Object::AggregateIterator' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ObjectAggregateIterator_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AggregateIterator");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3ObjectAggregateIterator_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3ObjectAggregateIterator_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3ObjectAggregateIterator_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Queue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Queue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Queue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::RandomVariableStream' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3RandomVariableStream_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "RandomVariableStream");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::SequentialRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SequentialRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SequentialRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt__");
    
        if (PyErr_Occurred()) PyErr_Clear();
        /* Import the 'ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >' class type map from module 'ns.core' */
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map");
        if (_cobj == NULL) {
            _PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map = new pybindgen::TypeMap;
            PyErr_Clear();
        } else {
            _PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map = reinterpret_cast<pybindgen::TypeMap*> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Time' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Time_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Time");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3Time_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3Time_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3Time_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::TraceSourceAccessor' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TraceSourceAccessor_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TraceSourceAccessor");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::TracedValue< ns3::Time >' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TracedValue__Ns3Time_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TracedValue__Ns3Time");
    
        if (PyErr_Occurred()) PyErr_Clear();
        PyObject *_cobj = PyObject_GetAttrString(module, (char*) "_PyNs3TracedValue__Ns3Time_wrapper_registry");
        if (_cobj == NULL) {
            _PyNs3TracedValue__Ns3Time_wrapper_registry = NULL;
            PyErr_Clear();
        } else {
            _PyNs3TracedValue__Ns3Time_wrapper_registry = reinterpret_cast< std::map<void*, PyObject*> *> (PyCObject_AsVoidPtr (_cobj));
            Py_DECREF(_cobj);
        }
    }
    /* Import the 'ns3::Trailer' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Trailer_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Trailer");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::TriangularRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TriangularRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TriangularRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::UniformRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3UniformRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "UniformRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::WeibullRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3WeibullRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "WeibullRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ZetaRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ZetaRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ZetaRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ZipfRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ZipfRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ZipfRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::AttributeAccessor' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AttributeAccessor_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AttributeAccessor");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::AttributeChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AttributeChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AttributeChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::AttributeValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AttributeValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AttributeValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::BooleanChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3BooleanChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "BooleanChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::BooleanValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3BooleanValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "BooleanValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::CallbackChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3CallbackChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "CallbackChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::CallbackImplBase' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3CallbackImplBase_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "CallbackImplBase");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::CallbackValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3CallbackValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "CallbackValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ConstantRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ConstantRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ConstantRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::DataRateChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3DataRateChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "DataRateChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::DataRateValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3DataRateValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "DataRateValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::DeterministicRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3DeterministicRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "DeterministicRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::DoubleValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3DoubleValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "DoubleValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EmpiricalRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EmpiricalRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EmpiricalRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EmptyAttributeAccessor' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EmptyAttributeAccessor_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EmptyAttributeAccessor");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EmptyAttributeChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EmptyAttributeChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EmptyAttributeChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EmptyAttributeValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EmptyAttributeValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EmptyAttributeValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EnumChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EnumChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EnumChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EnumValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EnumValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EnumValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ErlangRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ErlangRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ErlangRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::EventImpl' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3EventImpl_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "EventImpl");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ExponentialRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ExponentialRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ExponentialRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::GammaRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3GammaRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "GammaRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::IntegerValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3IntegerValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "IntegerValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv4AddressChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv4AddressChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv4AddressChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv4AddressValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv4AddressValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv4AddressValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv4MaskChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv4MaskChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv4MaskChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv4MaskValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv4MaskValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv4MaskValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv6AddressChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv6AddressChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv6AddressChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv6AddressValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv6AddressValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv6AddressValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv6PrefixChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv6PrefixChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv6PrefixChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Ipv6PrefixValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Ipv6PrefixValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Ipv6PrefixValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::LogNormalRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3LogNormalRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "LogNormalRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Mac48AddressChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Mac48AddressChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Mac48AddressChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Mac48AddressValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Mac48AddressValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Mac48AddressValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::NetDevice' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3NetDevice_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "NetDevice");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::NetDeviceQueue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3NetDeviceQueue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "NetDeviceQueue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::NetDeviceQueueInterface' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3NetDeviceQueueInterface_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "NetDeviceQueueInterface");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::NixVector' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3NixVector_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "NixVector");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Node' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Node_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Node");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::NormalRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3NormalRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "NormalRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ObjectFactoryChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ObjectFactoryChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ObjectFactoryChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ObjectFactoryValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ObjectFactoryValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ObjectFactoryValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::Packet' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3Packet_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "Packet");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::ParetoRandomVariable' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3ParetoRandomVariable_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "ParetoRandomVariable");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::QueueItem' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3QueueItem_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "QueueItem");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::StringChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3StringChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "StringChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::StringValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3StringValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "StringValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::TimeValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TimeValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TimeValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::TypeIdChecker' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TypeIdChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TypeIdChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::TypeIdValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3TypeIdValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "TypeIdValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::UintegerValue' class from module 'ns.core' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.core");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3UintegerValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "UintegerValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::AddressChecker' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AddressChecker_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AddressChecker");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    /* Import the 'ns3::AddressValue' class from module 'ns.network' */
    {
        PyObject *module = PyImport_ImportModule((char*) "ns.network");
        if (module == NULL) {
            return MOD_ERROR;
        }
        _PyNs3AddressValue_Type = (PyTypeObject*) PyObject_GetAttrString(module, (char*) "AddressValue");
    
        if (PyErr_Occurred()) PyErr_Clear();
    }
    PyModule_AddObject(m, (char *) "_PyNs3QueueDiscContainer_wrapper_registry", PyCObject_FromVoidPtr(&PyNs3QueueDiscContainer_wrapper_registry, NULL));
    /* Register the 'ns3::QueueDiscContainer' class */
    if (PyType_Ready(&PyNs3QueueDiscContainer_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "QueueDiscContainer", (PyObject *) &PyNs3QueueDiscContainer_Type);
    PyModule_AddObject(m, (char *) "_PyNs3QueueDiscFactory_wrapper_registry", PyCObject_FromVoidPtr(&PyNs3QueueDiscFactory_wrapper_registry, NULL));
    /* Register the 'ns3::QueueDiscFactory' class */
    if (PyType_Ready(&PyNs3QueueDiscFactory_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "QueueDiscFactory", (PyObject *) &PyNs3QueueDiscFactory_Type);
    PyModule_AddObject(m, (char *) "_PyNs3TrafficControlHelper_wrapper_registry", PyCObject_FromVoidPtr(&PyNs3TrafficControlHelper_wrapper_registry, NULL));
    /* Register the 'ns3::TrafficControlHelper' class */
    if (PyType_Ready(&PyNs3TrafficControlHelper_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "TrafficControlHelper", (PyObject *) &PyNs3TrafficControlHelper_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::PacketFilter), &PyNs3PacketFilter_Type);
    /* Register the 'ns3::PacketFilter' class */
    
    PyNs3PacketFilterMeta_Type.tp_base = Py_TYPE(&PyNs3Object_Type);
    /* Some fields need to be manually inheritted from the parent metaclass */
    PyNs3PacketFilterMeta_Type.tp_traverse = Py_TYPE(&PyNs3Object_Type)->tp_traverse;
    PyNs3PacketFilterMeta_Type.tp_clear = Py_TYPE(&PyNs3Object_Type)->tp_clear;
    PyNs3PacketFilterMeta_Type.tp_is_gc = Py_TYPE(&PyNs3Object_Type)->tp_is_gc;
    /* PyType tp_setattro is too restrictive */
    PyNs3PacketFilterMeta_Type.tp_setattro = PyObject_GenericSetAttr;
    PyType_Ready(&PyNs3PacketFilterMeta_Type);
    
    PyNs3PacketFilter_Type.tp_base = &PyNs3Object_Type;
    Py_TYPE(&PyNs3PacketFilter_Type) = &PyNs3PacketFilterMeta_Type;
    if (PyType_Ready(&PyNs3PacketFilter_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "PacketFilter", (PyObject *) &PyNs3PacketFilter_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::QueueDisc), &PyNs3QueueDisc_Type);
    /* Register the 'ns3::QueueDisc' class */
    PyNs3QueueDisc_Type.tp_base = &PyNs3Object_Type;
    if (PyType_Ready(&PyNs3QueueDisc_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "QueueDisc", (PyObject *) &PyNs3QueueDisc_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::QueueDiscClass), &PyNs3QueueDiscClass_Type);
    /* Register the 'ns3::QueueDiscClass' class */
    PyNs3QueueDiscClass_Type.tp_base = &PyNs3Object_Type;
    if (PyType_Ready(&PyNs3QueueDiscClass_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "QueueDiscClass", (PyObject *) &PyNs3QueueDiscClass_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::RedQueueDisc), &PyNs3RedQueueDisc_Type);
    /* Register the 'ns3::RedQueueDisc' class */
    PyNs3RedQueueDisc_Type.tp_base = &PyNs3QueueDisc_Type;
    if (PyType_Ready(&PyNs3RedQueueDisc_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "RedQueueDisc", (PyObject *) &PyNs3RedQueueDisc_Type);
    PyModule_AddObject(m, (char *) "_PyNs3RedQueueDiscStats_wrapper_registry", PyCObject_FromVoidPtr(&PyNs3RedQueueDiscStats_wrapper_registry, NULL));
    /* Register the 'ns3::RedQueueDisc::Stats' class */
    if (PyType_Ready(&PyNs3RedQueueDiscStats_Type)) {
        return MOD_ERROR;
    }
    PyDict_SetItemString((PyObject*) PyNs3RedQueueDisc_Type.tp_dict, (char *) "Stats", (PyObject *) &PyNs3RedQueueDiscStats_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::TrafficControlLayer), &PyNs3TrafficControlLayer_Type);
    /* Register the 'ns3::TrafficControlLayer' class */
    PyNs3TrafficControlLayer_Type.tp_base = &PyNs3Object_Type;
    if (PyType_Ready(&PyNs3TrafficControlLayer_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "TrafficControlLayer", (PyObject *) &PyNs3TrafficControlLayer_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::CoDelQueueDisc), &PyNs3CoDelQueueDisc_Type);
    /* Register the 'ns3::CoDelQueueDisc' class */
    PyNs3CoDelQueueDisc_Type.tp_base = &PyNs3QueueDisc_Type;
    if (PyType_Ready(&PyNs3CoDelQueueDisc_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "CoDelQueueDisc", (PyObject *) &PyNs3CoDelQueueDisc_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::FqCoDelFlow), &PyNs3FqCoDelFlow_Type);
    /* Register the 'ns3::FqCoDelFlow' class */
    PyNs3FqCoDelFlow_Type.tp_base = &PyNs3QueueDiscClass_Type;
    if (PyType_Ready(&PyNs3FqCoDelFlow_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "FqCoDelFlow", (PyObject *) &PyNs3FqCoDelFlow_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::FqCoDelQueueDisc), &PyNs3FqCoDelQueueDisc_Type);
    /* Register the 'ns3::FqCoDelQueueDisc' class */
    PyNs3FqCoDelQueueDisc_Type.tp_base = &PyNs3QueueDisc_Type;
    if (PyType_Ready(&PyNs3FqCoDelQueueDisc_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "FqCoDelQueueDisc", (PyObject *) &PyNs3FqCoDelQueueDisc_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::PfifoFastQueueDisc), &PyNs3PfifoFastQueueDisc_Type);
    /* Register the 'ns3::PfifoFastQueueDisc' class */
    PyNs3PfifoFastQueueDisc_Type.tp_base = &PyNs3QueueDisc_Type;
    if (PyType_Ready(&PyNs3PfifoFastQueueDisc_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "PfifoFastQueueDisc", (PyObject *) &PyNs3PfifoFastQueueDisc_Type);
    PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map.register_wrapper(typeid(ns3::PieQueueDisc), &PyNs3PieQueueDisc_Type);
    /* Register the 'ns3::PieQueueDisc' class */
    PyNs3PieQueueDisc_Type.tp_base = &PyNs3QueueDisc_Type;
    if (PyType_Ready(&PyNs3PieQueueDisc_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "PieQueueDisc", (PyObject *) &PyNs3PieQueueDisc_Type);
    PyModule_AddObject(m, (char *) "_PyNs3PieQueueDiscStats_wrapper_registry", PyCObject_FromVoidPtr(&PyNs3PieQueueDiscStats_wrapper_registry, NULL));
    /* Register the 'ns3::PieQueueDisc::Stats' class */
    if (PyType_Ready(&PyNs3PieQueueDiscStats_Type)) {
        return MOD_ERROR;
    }
    PyDict_SetItemString((PyObject*) PyNs3PieQueueDisc_Type.tp_dict, (char *) "Stats", (PyObject *) &PyNs3PieQueueDiscStats_Type);
    PyNs3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt____typeid_map.register_wrapper(typeid(ns3::QueueDiscItem), &PyNs3QueueDiscItem_Type);
    /* Register the 'ns3::QueueDiscItem' class */
    PyNs3QueueDiscItem_Type.tp_base = &PyNs3QueueItem_Type;
    if (PyType_Ready(&PyNs3QueueDiscItem_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "QueueDiscItem", (PyObject *) &PyNs3QueueDiscItem_Type);
    /* Register the 'std::vector< ns3::Ptr< ns3::QueueDisc > >' class */
    if (PyType_Ready(&Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt___Type)) {
        return MOD_ERROR;
    }
    if (PyType_Ready(&Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "Std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__", (PyObject *) &Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt___Type);
    PyModule_AddObject(m, (char *) "Std__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter", (PyObject *) &Pystd__vector__lt___ns3__Ptr__lt___ns3__QueueDisc___gt_____gt__Iter_Type);
    /* Register the 'std::vector< short unsigned int >' class */
    if (PyType_Ready(&Pystd__vector__lt___short_unsigned_int___gt___Type)) {
        return MOD_ERROR;
    }
    if (PyType_Ready(&Pystd__vector__lt___short_unsigned_int___gt__Iter_Type)) {
        return MOD_ERROR;
    }
    PyModule_AddObject(m, (char *) "Std__vector__lt___short_unsigned_int___gt__", (PyObject *) &Pystd__vector__lt___short_unsigned_int___gt___Type);
    PyModule_AddObject(m, (char *) "Std__vector__lt___short_unsigned_int___gt__Iter", (PyObject *) &Pystd__vector__lt___short_unsigned_int___gt__Iter_Type);
    {
        PyObject *tmp_value;
         // ns3::QueueDisc::WAKE_ROOT
        tmp_value = PyLong_FromLong(ns3::QueueDisc::WAKE_ROOT);
        PyDict_SetItemString((PyObject*) PyNs3QueueDisc_Type.tp_dict, "WAKE_ROOT", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::QueueDisc::WAKE_CHILD
        tmp_value = PyLong_FromLong(ns3::QueueDisc::WAKE_CHILD);
        PyDict_SetItemString((PyObject*) PyNs3QueueDisc_Type.tp_dict, "WAKE_CHILD", tmp_value);
        Py_DECREF(tmp_value);
    }
    {
        PyObject *tmp_value;
         // ns3::RedQueueDisc::DTYPE_NONE
        tmp_value = PyLong_FromLong(ns3::RedQueueDisc::DTYPE_NONE);
        PyDict_SetItemString((PyObject*) PyNs3RedQueueDisc_Type.tp_dict, "DTYPE_NONE", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::RedQueueDisc::DTYPE_FORCED
        tmp_value = PyLong_FromLong(ns3::RedQueueDisc::DTYPE_FORCED);
        PyDict_SetItemString((PyObject*) PyNs3RedQueueDisc_Type.tp_dict, "DTYPE_FORCED", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::RedQueueDisc::DTYPE_UNFORCED
        tmp_value = PyLong_FromLong(ns3::RedQueueDisc::DTYPE_UNFORCED);
        PyDict_SetItemString((PyObject*) PyNs3RedQueueDisc_Type.tp_dict, "DTYPE_UNFORCED", tmp_value);
        Py_DECREF(tmp_value);
    }
    {
        PyObject *tmp_value;
         // ns3::FqCoDelFlow::INACTIVE
        tmp_value = PyLong_FromLong(ns3::FqCoDelFlow::INACTIVE);
        PyDict_SetItemString((PyObject*) PyNs3FqCoDelFlow_Type.tp_dict, "INACTIVE", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::FqCoDelFlow::NEW_FLOW
        tmp_value = PyLong_FromLong(ns3::FqCoDelFlow::NEW_FLOW);
        PyDict_SetItemString((PyObject*) PyNs3FqCoDelFlow_Type.tp_dict, "NEW_FLOW", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::FqCoDelFlow::OLD_FLOW
        tmp_value = PyLong_FromLong(ns3::FqCoDelFlow::OLD_FLOW);
        PyDict_SetItemString((PyObject*) PyNs3FqCoDelFlow_Type.tp_dict, "OLD_FLOW", tmp_value);
        Py_DECREF(tmp_value);
    }
    {
        PyObject *tmp_value;
         // ns3::PieQueueDisc::NO_BURST
        tmp_value = PyLong_FromLong(ns3::PieQueueDisc::NO_BURST);
        PyDict_SetItemString((PyObject*) PyNs3PieQueueDisc_Type.tp_dict, "NO_BURST", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::PieQueueDisc::IN_BURST
        tmp_value = PyLong_FromLong(ns3::PieQueueDisc::IN_BURST);
        PyDict_SetItemString((PyObject*) PyNs3PieQueueDisc_Type.tp_dict, "IN_BURST", tmp_value);
        Py_DECREF(tmp_value);
         // ns3::PieQueueDisc::IN_BURST_PROTECTING
        tmp_value = PyLong_FromLong(ns3::PieQueueDisc::IN_BURST_PROTECTING);
        PyDict_SetItemString((PyObject*) PyNs3PieQueueDisc_Type.tp_dict, "IN_BURST_PROTECTING", tmp_value);
        Py_DECREF(tmp_value);
    }
    submodule = inittraffic_control_FatalImpl();
    if (submodule == NULL) {
        return MOD_ERROR;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "FatalImpl", submodule);
    submodule = inittraffic_control_Hash();
    if (submodule == NULL) {
        return MOD_ERROR;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "Hash", submodule);
    submodule = inittraffic_control_TracedValueCallback();
    if (submodule == NULL) {
        return MOD_ERROR;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "TracedValueCallback", submodule);
    submodule = inittraffic_control_internal();
    if (submodule == NULL) {
        return MOD_ERROR;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "internal", submodule);
    return MOD_RETURN(m);
}
