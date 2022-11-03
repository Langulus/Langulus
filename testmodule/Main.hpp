///                                                                           
/// Langulus::Framework                                                       
/// Copyright(C) 2016 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Langulus.hpp>

using namespace Langulus;
using namespace Langulus::Flow;
using namespace Langulus::Anyness;
using namespace Langulus::Entity;

class TestModule : public Module {
   LANGULUS(ABSTRACT) false;

   TestModule(Runtime* runtime, const Any&) noexcept
      : Module {MetaOf<TestModule>(), runtime} {}

   virtual void Update(Time) final {

   }
};

struct SomeReflectedType1 {

};

struct SomeReflectedType2 {

};

struct SomeCategory {

};

LANGULUS_DEFINE_MODULE(TestModule, 1, "TestModule", "Just some module for testing", ""
   , MetaOf<SomeCategory>()
   , SomeReflectedType1, SomeReflectedType2
)