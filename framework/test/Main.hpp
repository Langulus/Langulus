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


/// See https://github.com/catchorg/Catch2/blob/devel/docs/tostring.md        
#define LANGULUS_EXCEPTION_HANDLER \
   CATCH_TRANSLATE_EXCEPTION(::Langulus::Exception const& ex) { \
      const Text serialized {ex}; \
      return ::std::string {Token {serialized}}; \
   }
