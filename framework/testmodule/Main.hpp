///                                                                           
/// Langulus::Framework                                                       
/// Copyright(C) 2016 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Entity/Thing.hpp>

using namespace Langulus;
using namespace Entity;


class TestModule : public A::Module {
   LANGULUS(ABSTRACT) false;
   LANGULUS_BASES(Module);

   TestModule(Runtime* runtime, const Any&) noexcept
      : Module {MetaOf<TestModule>(), runtime} {}
};

struct SomeReflectedType1 {

};

struct SomeReflectedType2 {

};

struct SomeCategory {

};

