///                                                                           
/// Langulus                                                                  
/// Copyright (c) 2016 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Entity/Thing.hpp>
#include <Langulus/Testing.hpp>


SCENARIO("Framework initialization and shutdown, 10 times", "[framework]") {
   static Allocator::State memoryState;

   for (int repeat = 0; repeat != 100; ++repeat) {
      GIVEN(std::string("Init and shutdown cycle #") + std::to_string(repeat)) {
         // Create root entity                                          
         Thing root;
         root.AddTrait(Traits::Name {"ROOT"});

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

         // Check for memory leaks after each cycle                     
         REQUIRE(memoryState.Assert());
      }
   }
}
