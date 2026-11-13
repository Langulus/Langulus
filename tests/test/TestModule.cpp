///                                                                           
/// Langulus                                                                  
/// Copyright (c) 2016 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Thing.hpp>
#include <Langulus/Testing.hpp>
#include <Langulus/Allocator.hpp>

using namespace Langulus;
using Things::Thing;


SCENARIO("Framework initialization and shutdown, 10 times") {
   static MemoryState memoryState;

   GIVEN("Init and shutdown cycles") {
      for (int repeat = 0; repeat != 100; ++repeat) {
         // Create root entity                                          
         Thing root;
         root.AddTag(Tags::Name {"ROOT"});

         // Create runtime at the root                                  
         auto runtime = root.CreateRuntime();
         REQUIRE(runtime);

         // Create runtime at the root, again, make sure it's the same  
         auto runtime2 = root.CreateRuntime();
         REQUIRE(runtime2);
         REQUIRE(runtime == runtime2);

         // Load test module                                            
         auto module = root.LoadMod("Test");
         REQUIRE(module);
         REQUIRE(module->GetRuntime() == runtime);
         #if LANGULUS_FEATURE(MANAGED_REFLECTION)
            REQUIRE(runtime->GetDependencyToken("SomeReflectedType1").IsValid());
            REQUIRE(runtime->GetModulesToken("TestModule").GetCount() == 1);
         #endif

         // Load test module again, make sure it's the same instance    
         auto module2 = root.LoadMod("Test");
         REQUIRE(module2);
         REQUIRE(module2 == module);
         REQUIRE(module2->GetRuntime() == runtime);
         #if LANGULUS_FEATURE(MANAGED_REFLECTION)
            REQUIRE(runtime->GetDependencyToken("SomeReflectedType1").IsValid());
            REQUIRE(runtime->GetModulesToken("TestModule").GetCount() == 1);
         #endif

         WHEN("The hierarchy is updated") {
            // Update once                                              
            root.Update({});
            root.DumpHierarchy();
         }

         REQUIRE(memoryState.Assert());
         REQUIRE_FALSE(Allocator::CollectGarbage());
      }
   }
}
