///                                                                           
/// Langulus::Framework                                                       
/// Copyright(C) 2016 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <catch2/catch.hpp>
#include <any>
#include <vector>

/// See https://github.com/catchorg/Catch2/blob/devel/docs/tostring.md        
CATCH_TRANSLATE_EXCEPTION(::Langulus::Exception const& ex) {
   const Text serialized {ex};
   return ::std::string {Token {serialized}};
}


SCENARIO("Framework initialization and shutdown", "[framework]") {
   GIVEN("A root entity") {
      // Create root entity                                             
      Thing root;
      root.AddTrait(Traits::Name {"ROOT"_text});

      // Create runtime at the root                                     
      auto runtime = root.CreateRuntime();

      // Load test module                                               
      auto module = root.LoadMod("Test");
      REQUIRE(module);
      REQUIRE(module->GetRuntime() == runtime);
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
   }
}
