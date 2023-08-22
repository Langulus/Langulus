///                                                                           
/// Langulus::Framework                                                       
/// Copyright(C) 2016 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Entity/Thing.hpp>
#include <catch2/catch.hpp>
#include <any>
#include <vector>

LANGULUS_EXCEPTION_HANDLER

SCENARIO("Framework initialization and shutdown, 10 times", "[framework]") {
   Allocator::State memoryState;

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
         REQUIRE(runtime->GetDependency("SomeReflectedType1").IsValid());
         REQUIRE(runtime->GetModules("TestModule").GetCount() == 1);

         // Load test module again, make sure it's the same instance    
         auto module2 = root.LoadMod("Test");
         REQUIRE(module2);
         REQUIRE(module2 == module);
         REQUIRE(module2->GetRuntime() == runtime);
         REQUIRE(runtime->GetDependency("SomeReflectedType1").IsValid());
         REQUIRE(runtime->GetModules("TestModule").GetCount() == 1);

         WHEN("The hierarchy is updated") {
            // Update once                                              
            root.Update(Time::zero());

            THEN("Various traits change") {
               root.DumpHierarchy();

               REQUIRE(true);
            }
         }

         // Check for memory leaks after each cycle                     
         REQUIRE(memoryState.Assert());
      }
   }
}
