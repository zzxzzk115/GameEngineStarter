/**
 * @file AndroidOut.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief 
 * @version 0.1.0
 * @date 2023-12-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SomeEngineRuntime/Platform/Android/AndroidOut.h"

AndroidOut androidOut("AO");
std::ostream aout(&androidOut);