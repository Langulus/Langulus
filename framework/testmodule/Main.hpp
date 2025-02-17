///                                                                           
/// Langulus test module                                                      
/// Copyright (c) 2016 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
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

