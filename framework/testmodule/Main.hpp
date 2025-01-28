///                                                                           
/// Langulus::Module::TestModule                                              
/// Copyright (c) 2016 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Langulus/Entity/Thing.hpp>

using namespace Langulus;


class TestModule final : public A::Module {
   LANGULUS(ABSTRACT) false;
   LANGULUS_BASES(Module);

   TestModule(Runtime* runtime, const Many&) noexcept
      : Resolvable {this}
      , Module     {runtime} {}

   void Teardown() {}
};

struct SomeReflectedType1 {

};

struct SomeReflectedType2 {

};

struct SomeCategory {

};

