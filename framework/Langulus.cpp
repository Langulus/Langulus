///                                                                           
/// Langulus                                                                  
/// Copyright (c) 2024 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Entity/Thing.hpp>
#include <Langulus/Economy.hpp>

using namespace Langulus;


namespace
{
   Logger::ToHTML* html_output = nullptr;
   Thing* root = nullptr;
   bool initialized = false;
}


///                                                                           
/// A plain C compliant exports for use in whatever you want                  
/// Profoundly unsafe and not recommended                                     
///                                                                           
extern "C"
{
   // Main functionality                                                
   LANGULUS_EXPORT() void* LangulusInit();
   LANGULUS_EXPORT() void* LangulusRoot();
   LANGULUS_EXPORT() void* LangulusEconomy();
   LANGULUS_EXPORT() void* LangulusResource(void*, const void*, int);
   LANGULUS_EXPORT() void* LangulusConverter(void*, const void*, int);
   LANGULUS_EXPORT() bool  LangulusUpdate(void*, int, int);
   LANGULUS_EXPORT() void  LangulusExit();
   LANGULUS_EXPORT() void* LangulusLoadMod(void*, const void*, int, const void* = nullptr, int = 0);
   LANGULUS_EXPORT() void* LangulusCreateThing(void*, const void* = nullptr, int = 0);
   LANGULUS_EXPORT() void* LangulusCreateUnit(void*, const void*, int, const void* = nullptr, int = 0);

   // Logging                                                           
   LANGULUS_EXPORT() void  LangulusLog(int, const void*, int);
   LANGULUS_EXPORT() void  LangulusLogTab(int, const void*, int);
   LANGULUS_EXPORT() void  LangulusLogTabEnd();
                           
   LANGULUS_EXPORT() void  LangulusLogLine(const void*, int);
   LANGULUS_EXPORT() void  LangulusLogAppend(const void*, int);
   LANGULUS_EXPORT() void  LangulusDumpHierarchy();

   LANGULUS_EXPORT() int32_t LangulusResourceQuantity(void*);
   LANGULUS_EXPORT() int   LangulusResourceQuantityLocal(void*, float x, float y, float r);
                           
   LANGULUS_EXPORT() int   LangulusResourceInstanceCount(void*);
   LANGULUS_EXPORT() int   LangulusResourceInstanceCountLocal(void*, float x, float y, float r);

   LANGULUS_EXPORT() float LangulusResourceSupply(void*);
   LANGULUS_EXPORT() float LangulusResourceSupplyLocal(void*, float x, float y, float r);

   LANGULUS_EXPORT() float LangulusResourceDemand(void*);
   LANGULUS_EXPORT() float LangulusResourceDemandLocal(void*, float x, float y, float r);

   LANGULUS_EXPORT() float LangulusResourceConsumption(void*);
   LANGULUS_EXPORT() float LangulusResourceConsumptionLocal(void*, float x, float y, float r);

   LANGULUS_EXPORT() void*  LangulusResourceInstance(void*, float x, float y);
   LANGULUS_EXPORT() void** LangulusResourceInstancesLocalBegin(void*, float x, float y, float r);
   LANGULUS_EXPORT() void   LangulusResourceInstancesLocalEnd(void**);

   LANGULUS_EXPORT() void*  LangulusConverterInstance(void*, float x, float y);
   LANGULUS_EXPORT() void** LangulusConverterInstancesLocalBegin(void*, float x, float y, float r);
   LANGULUS_EXPORT() void   LangulusConverterInstancesLocalEnd(void**);
}


///                                                                           
/// Implementation details below                                              
///                                                                           

/// Initialize the framework                                                  
///   @return a handle to the root object                                     
void* LangulusInit() {
   if (initialized)
      return root;

   // Redirect all logging to an external HTML file                     
   html_output = new Logger::ToHTML {"langulus.htm"};
   Logger::AttachRedirector(html_output);
   root = new Thing;
   root->SetName("ROOT");
   root->CreateRuntime();
   root->CreateFlow();
   initialized = true;
   return root;
}

/// Get the framework's root Thing                                            
///   @return a handle to the root object                                     
void* LangulusRoot() {
#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusRoot()");
      return nullptr;
   }
#endif

   return root;
}

/// Get the framework's economy component inside root                         
///   @return a handle to the economy module                                  
void* LangulusEconomy() {
#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusRoot()");
      return nullptr;
   }
#endif

   auto& economies = root->GetRuntime()->GetModules<A::Economy>();
   LANGULUS_ASSERT(economies, Module, "Can't retrieve economy - no economy module available");
   return economies.template As<A::Economy*>();
}

/// Get a resource definition                                                 
///   @param economy - the economy module                                     
///   @param name - resource name                                             
///   @param name_size - the number of characters in provided 'name'          
///   @return the resource unit handle                                        
void* LangulusResource(void* economy, const void* name, int name_size) {
   Logger::Network("LangulusResource...");

#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusResource()");
      return nullptr;
   }
#endif

   if (not economy)
      economy = LangulusEconomy();

#if LANGULUS(SAFE)
   if (not name) {
      Logger::Error("Invalid resource name pointer on LangulusResource");
      return nullptr;
   }

   if (name_size < 1) {
      Logger::Error("Empty resource name on LangulusResource");
      return nullptr;
   }
#endif

   Token token {
      static_cast<const char*>(name),
      static_cast<std::size_t>(name_size)
   };
   auto typed = reinterpret_cast<A::Economy*>(economy);

#if LANGULUS(SAFE)
   if (name_size > 4096) {
      Logger::Error("Resource name on LangulusResource is too long: ", token);
      return nullptr;
   }
#endif
   Logger::Network("Getting resource: ", token);

   auto resource = typed->GetResource(token);

#if LANGULUS(SAFE)
   if (not resource) {
      Logger::Error("No such resources on LangulusResource: ", token);
      return 0;
   }
#endif

   return const_cast<A::Resource*>(resource);
}

/// Get a converter definition                                                
///   @param economy - the economy module                                     
///   @param name - converter name                                            
///   @param name_size - the number of characters in provided 'name'          
///   @return the converter unit handle                                       
void* LangulusConverter(void* economy, const void* name, int name_size) {
#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusConverter()");
      return nullptr;
   }
#endif

   if (not economy)
      economy = LangulusEconomy();

#if LANGULUS(SAFE)
   if (not name) {
      Logger::Error("Invalid converter name pointer on LangulusConverter");
      return nullptr;
   }

   if (name_size < 1) {
      Logger::Error("Empty converter name on LangulusConverter");
      return nullptr;
   }
#endif

   Token token {
      static_cast<const char*>(name),
      static_cast<std::size_t>(name_size)
   };
   auto typed = reinterpret_cast<A::Economy*>(economy);

#if LANGULUS(SAFE)
   if (name_size > 4096) {
      Logger::Error("Converter name on LangulusConverter is too long: ", token);
      return nullptr;
   }
#endif

   auto converter = typed->GetConverter(token);

#if LANGULUS(SAFE)
   if (not converter) {
      Logger::Error("No such converters on LangulusConverter: ", token);
      return 0;
   }
#endif

   return const_cast<A::Converter*>(converter);
}

/// Update the hierarchy, starting with the provided Thing                    
///   @param thing - the Thing to start updating from - uses root if nullptr  
///   @param deltaTime - amount of time units, depends on timeScale           
///   @param timeLevel - the level of time passed                             
///   @note time is calculated like so: deltaTime*10^(timeScale*3) seconds    
///      you would usually send time as LangulusUpdate(nullptr, 16, -1)       
///      which means 0.016 seconds (aka 60 frames per second)                 
///   @return false if Langulus has requested an exit                         
bool LangulusUpdate(void* thing, int deltaTime, int timeLevel) {
#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusUpdate()");
      return false;
   }
#endif

   if (not thing)
      thing = root;

   Time converted;
   switch (timeLevel) {
   case -3:
   {
      ::std::chrono::nanoseconds t {deltaTime};
      converted = ::std::chrono::duration_cast<typename Time::Base>(t);
      break;
   }
   case -2:
   {
      ::std::chrono::microseconds t {deltaTime};
      converted = ::std::chrono::duration_cast<typename Time::Base>(t);
      break;
   }
   case -1:
   {
      ::std::chrono::milliseconds t {deltaTime};
      converted = ::std::chrono::duration_cast<typename Time::Base>(t);
      break;
   }
   case  0:
   {
      ::std::chrono::seconds t {deltaTime};
      converted = ::std::chrono::duration_cast<typename Time::Base>(t);
      break;
   }
   default:
      Logger::Fatal("Langulus doesn't support that time scale yet: ", timeLevel);
      return false;
   }

   Thing* typed = reinterpret_cast<Thing*>(thing);
   return typed->Update(converted);
}

/// Shutdown the framework                                                    
///   @attention invalidates all handles                                      
void LangulusExit() {
   if (not initialized)
      return;

   root->Reference(-1);
   delete root;
   root = nullptr;
   (void) Allocator::CollectGarbage();
   Logger::DettachRedirector(html_output);
   delete html_output;
   html_output = nullptr;
   initialized = false;
}

/// Load a langulus plug-in                                                   
///   @param thing - load plug-in in this Thing's context                     
///      will use root if nullptr                                             
///   @param name - the name of the plug-in                                   
///   @param name_size - the number of characters in provided 'name'          
///   @param desc - the plug-in descriptor (optional)                         
///   @param desc_size - the number of characters in provided 'desc'          
///   @return a handle to the loaded module                                   
void* LangulusLoadMod(void* thing, const void* name, int name_size, const void* desc, int desc_size) {
   Logger::Info("Loading mod ", Token {
      static_cast<const char*>(name),
      static_cast<std::size_t>(name_size)
   }, "...");

#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusLoadMod()");
      return nullptr;
   }
#endif

   if (not thing)
      thing = root;

#if LANGULUS(SAFE)
   if (not name) {
      Logger::Error("Invalid module name pointer on LangulusLoadMod");
      return nullptr;
   }

   if (name_size < 1) {
      Logger::Error("Empty module name on LangulusLoadMod");
      return nullptr;
   }
#endif

   Token token {
      static_cast<const char*>(name),
      static_cast<std::size_t>(name_size)
   };
   Thing* typed = reinterpret_cast<Thing*>(thing);

#if LANGULUS(SAFE)
   if (name_size > 4096) {
      Logger::Error("Module name on LangulusLoadMod is too long: ", token);
      return nullptr;
   }
#endif

   try {
      if (desc and desc_size > 0) {
         // Parse a descriptor                                          
         Token code {
            static_cast<const char*>(desc),
            static_cast<std::size_t>(desc_size)
         };
         return typed->LoadModPath(token, Code(code).Parse());
      }

      return typed->LoadModPath(token);
   }
   catch (...) {
      Logger::Error("Exception while loading module: ", token);
      return nullptr;
   }
}

/// Create a child Thing in the context of a Thing                            
///   @param thing - create in this context (will use root if nullptr)        
///   @param desc - the descriptor for the new Thing                          
///   @param size - the number of characters in provided 'desc'               
///   @return a handle to the new thing                                       
void* LangulusCreateThing(void* thing, const void* desc, int desc_size) {
#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusCreateThing()");
      return nullptr;
   }
#endif

   if (not thing)
      thing = root;

   Thing* typed = reinterpret_cast<Thing*>(thing);

   try {
      if (desc and desc_size > 0) {
         // Parse a descriptor                                          
         Token code {
            static_cast<const char*>(desc),
            static_cast<std::size_t>(desc_size)
         };
         return typed->CreateChild(Code(code).Parse()).Get();
      }

      return typed->CreateChild().Get();
   }
   catch (...) {
      Logger::Error("Exception while creating child");
      return nullptr;
   }
}

/// Create a Unit in the context of a Thing                                   
///   @param thing - create in this context (will use root if nullptr)        
///   @param name - the name of the unit                                      
///   @param name_size - the number of characters in provided 'name'          
///   @param desc - the descriptor for the new Unit                           
///   @param desc_size - the number of characters in provided 'desc'          
///   @return a handle to the new unit                                        
void* LangulusCreateUnit(void* thing, const void* name, int name_size, const void* desc, int desc_size) {
#if LANGULUS(SAFE)
   if (not initialized) {
      Logger::Fatal("Langulus wasn't initialized - call LangulusInit() prior to LangulusCreateUnit()");
      return nullptr;
   }
#endif

   if (not thing)
      thing = root;

#if LANGULUS(SAFE)
   if (not name) {
      Logger::Error("Invalid unit name pointer on LangulusCreateUnit");
      return nullptr;
   }

   if (name_size < 1) {
      Logger::Error("Empty unit name on LangulusCreateUnit");
      return nullptr;
   }
#endif

   Token token {
      static_cast<const char*>(name),
      static_cast<std::size_t>(name_size)
   };
   Thing* typed = reinterpret_cast<Thing*>(thing);

#if LANGULUS(SAFE)
   if (name_size > 4096) {
      Logger::Error("Unit name on LangulusCreateUnit is too long: ", token);
      return nullptr;
   }
#endif

   try {
      if (desc and desc_size > 0) {
         // Parse a descriptor                                          
         Token code {
            static_cast<const char*>(desc),
            static_cast<std::size_t>(desc_size)
         };
         return typed->CreateUnitToken(token, Code(code).Parse()).As<A::Unit*>();
      }

      return typed->CreateUnitToken(token).As<A::Unit*>();
   }
   catch (...) {
      Logger::Error("Exception while creating unit: ", token);
      return nullptr;
   }
}


/// Log a message with specific formatting on a new line                      
///   @param type - type of the message, see Logger::Intent for definitions   
///   @param text - the start of the text memory to log                       
///   @param text_size - the number of bytes in 'text'                        
void LangulusLog(int type, const void* text, int text_size) {
   const auto t = static_cast<Logger::Intent>(type);
   if (not text or text_size < 1 or type < 0 or t >= Logger::Intent::Ignore)
      return;

   Logger::Instance << t;
   Logger::Instance.NewLine();
   Logger::Instance << Token {
      static_cast<const char*>(text),
      static_cast<std::size_t>(text_size)
   };
}

/// Log a message with specific formatting on a new line, and indent all      
/// the next lines until LangulusLogTabEnd is called                          
///   @param type - type of the message, see Logger::Intent for definitions   
///   @param text - the start of the text memory to log                       
///   @param text_size - the number of bytes in 'text'                        
void LangulusLogTab(int type, const void* text, int text_size) {
   LangulusLog(type, text, text_size);
   Logger::Instance << Logger::Tab;
}

/// Untab all next messages                                                   
void LangulusLogTabEnd() {
   Logger::Instance << Logger::Untab;
}

/// Just write a new line, with whatever formatting was set prior             
///   @param text - the start of the text memory to log                       
///   @param text_size - the number of bytes in 'text'                        
void LangulusLogLine(const void* text, int text_size) {
   Logger::Line(Token {
      static_cast<const char*>(text),
      static_cast<std::size_t>(text_size)
   });
}

/// Just write on the same line, with whatever formatting was set prior       
///   @param text - the start of the text memory to log                       
///   @param text_size - the number of bytes in 'text'                        
void LangulusLogAppend(const void* text, int text_size) {
   Logger::Append(Token {
      static_cast<const char*>(text),
      static_cast<std::size_t>(text_size)
   });
}

/// Logs the Thing hierarchy, starting from the root                          
void LangulusDumpHierarchy() {
   root->DumpHierarchy();
}

/// Get the quantity of a resource                                            
///   @param res - the resource definition                                    
///   @return the quantity                                                    
int32_t LangulusResourceQuantity(void* res) {
   Logger::Network("Taking quantity of resource: ", res);

   #if LANGULUS(SAFE)
      if (not res) {
         Logger::Error("Bad resource handle in LangulusResourceQuantity");
         return 0;
      }
   #endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetQuantity();
}

/// Get the quantity of a resource in a given area                            
///   @param res - the resource definition                                    
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the quantity                                                    
int LangulusResourceQuantityLocal(void* res, float x, float y, float r) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceQuantityLocal");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetQuantityLocal(A::Resource::Place {x, y}, r);
}

/// Get the instance count of a resource                                      
///   @param res - the resource definition                                    
///   @return the number of instances                                         
int LangulusResourceInstanceCount(void* res) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceInstanceCount");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetQuantity();
}

/// Get the instance count of a resource in a given area                      
///   @param res - the resource definition                                    
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the number of instances                                         
int LangulusResourceInstanceCountLocal(void* res, float x, float y, float r) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceInstanceCountLocal");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetQuantityLocal(A::Resource::Place {x, y}, r);
}

/// Get the supply of a resource                                              
///   @param res - the resource definition                                    
///   @return the supply (per tick)                                           
float LangulusResourceSupply(void* res) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceSupply");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetSupply();
}

/// Get the supply of a resource in a given area                              
///   @param res - the resource definition                                    
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the supply (per tick)                                           
float LangulusResourceSupplyLocal(void* res, float x, float y, float r) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceSupplyLocal");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetSupplyLocal(A::Resource::Place {x, y}, r);
}

/// Get the demand of a resource                                              
///   @param res - the resource definition                                    
///   @return the supply (per tick)                                           
float LangulusResourceDemand(void* res) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceDemand");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetDemand();
}

/// Get the demand of a resource in a given area                              
///   @param res - the resource definition                                    
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the supply (per tick)                                           
float LangulusResourceDemandLocal(void* res, float x, float y, float r) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceDemandLocal");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetDemandLocal(A::Resource::Place {x, y}, r);
}

/// Get the consumption of a resource                                         
///   @param res - the resource definition                                    
///   @return the supply (per tick)                                           
float LangulusResourceConsumption(void* res) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceConsumption");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetConsumption();
}

/// Get the consumption of a resource in a given area                         
///   @param res - the resource definition                                    
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the supply (per tick)                                           
float LangulusResourceConsumptionLocal(void* res, float x, float y, float r) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceConsumptionLocal");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return resource->GetConsumptionLocal(A::Resource::Place {x, y}, r);
}

/// Get resource instance at a position                                       
///   @param resource - the resource definition                               
///   @param x, y - position on the map                                       
///   @return the instance, if any                                            
void* LangulusResourceInstance(void* res, float x, float y) {
#if LANGULUS(SAFE)
   if (not res) {
      Logger::Error("Bad resource handle in LangulusResourceInstance");
      return 0;
   }
#endif
   auto resource = static_cast<A::Resource*>(res);
   return const_cast<A::ResourceInstance*>(resource->At(A::Resource::Place {x, y}));
}

/// Get all resource instances at a position                                  
///   @attention the list has to be destroyed with a call to                  
///      LangulusResourceInstancesLocalEnd                                    
///   @param res - the resource definition                                    
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the instance, if any                                            
void** LangulusResourceInstancesLocalBegin(void* res, float x, float y, float r) {
   TODO();
   return nullptr;
}

void LangulusResourceInstancesLocalEnd(void** handle) {
   TODO();
}

/// Get converter instance at a position                                      
///   @param conv - the converter definition                                  
///   @param x, y - position on the map                                       
///   @return the instance, if any                                            
void* LangulusConverterInstance(void* conv, float x, float y) {
#if LANGULUS(SAFE)
   if (not conv) {
      Logger::Error("Bad converter handle in LangulusConverterInstance");
      return 0;
   }
#endif
   auto converter = static_cast<A::Converter*>(conv);
   return const_cast<A::ConverterInstance*>(converter->At(A::Converter::Place {x, y}));
}

/// Get all converter instances at a position                                 
///   @attention the list has to be destroyed with a call to                  
///      LangulusConverterInstancesLocalEnd                                   
///   @param conv - the converter definition                                  
///   @param x, y - position on the map                                       
///   @param r - radius around the position                                   
///   @return the instance, if any                                            
void** LangulusConverterInstancesLocalBegin(void* conv, float x, float y, float r) {
   TODO();
   return nullptr;
}

void LangulusConverterInstancesLocalEnd(void** handle) {
   TODO();
}
