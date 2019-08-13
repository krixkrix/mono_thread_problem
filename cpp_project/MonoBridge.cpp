#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/threads.h>

#include "MonoBridge.h"

const char * DotNetAssembly = "mytest.exe";
const char * nameSpace = "mytest";
const char * nameClass = "MainClass";

static MonoDomain *domain = 0;
static MonoObject *MonoClassInstance = 0;
static MonoMethod* mmFoo = 0;
static unsigned int handle = 0;


/**
 *  MonoBridge makes the c# class MainClass available for the c++ world
 *  Error handling omitted.
 **/
MonoBridge::MonoBridge()
{
    mono_config_parse(NULL);

    // load and open assembly in a MonoDomain.
    domain = mono_jit_init (DotNetAssembly);
    MonoAssembly *assembly = mono_domain_assembly_open (domain, DotNetAssembly);

    MonoImage *image = mono_assembly_get_image(assembly);
    MonoClass * monoClass = mono_class_from_name (image, nameSpace, nameClass);

    // find method
    MonoMethodDesc* monoMethodDesc = mono_method_desc_new ("mytest.MainClass:Foo", 1);
    mmFoo = mono_method_desc_search_in_class (monoMethodDesc, monoClass);

    // create mono object
    MonoClassInstance = mono_object_new (domain, monoClass);
    mono_runtime_object_init (MonoClassInstance);
    handle = mono_gchandle_new (MonoClassInstance, true);
}

void MonoBridge::foo()
{
    mono_thread_attach(mono_get_root_domain());
    MonoObject *result = mono_runtime_invoke (mmFoo, MonoClassInstance, NULL, NULL);
}
