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

using uint = unsigned int;

SCENARIO("Framework initialization and shutdown", "[framework]") {
   GIVEN("A root entity") {
      // Create root entity                                             
      Thing root;
      root.AddTrait(Traits::Name {"ROOT"_text});

      // Create runtime at the root                                     
      root.CreateRuntime();

      // Load test module                                               
      root.LoadMod("Test");

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
