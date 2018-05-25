///////////////////////////////////////////////////////////////////////////////
/// 
/// Authors: Joshua Davis
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

// The first thing we do is detect the platform.
// The next thing we do is define macros that all platforms may use
// We also ignore any compiler or platform specific warnings here
#include "Platform.hpp"

#include <algorithm>
#include <ctype.h>
#include <cstddef>
#include <utility>
#include <typeinfo>
#include <new>
#include <stdarg.h>
#include <climits>
#include <string>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <setjmp.h>
#include <ctime>
#include <limits>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cfloat>
#include <malloc.h>

namespace Zero
{

class ZeroNoImportExport CommonLibrary
{
public:
  static void Initialize();
  static void Shutdown();
};

}//namespace Zero

#include "Utility/Standard.hpp"
#include "Utility/Typedefs.hpp"
#include "Time.hpp"
#include "Utility/Misc.hpp"
#include "Utility/Guid.hpp"
#include "Containers/TypeTraits.hpp"
#include "Utility/BitTypes.hpp"
#include "Utility/BitMath.hpp"
#include "Platform/Atomic.hpp"
#include "Containers/InList.hpp"
#include "Containers/ArrayMap.hpp"
#include "Containers/ArraySet.hpp"
#include "Containers/BlockArray.hpp"
#include "Containers/ByteBuffer.hpp"
#include "Containers/CyclicArray.hpp"
#include "Containers/OwnedArray.hpp"
#include "Containers/SortedArray.hpp"
#include "Containers/UnsortedMap.hpp"
#include "Containers/OrderedHashMap.hpp"
#include "Containers/OrderedHashSet.hpp"
#include "Diagnostic/Console.hpp"
#include "Diagnostic/Diagnostic.hpp"
#include "Containers/Algorithm.hpp"
#include "Containers/Allocator.hpp"
#include "Containers/Array.hpp"
#include "Containers/ContainerCommon.hpp"
#include "Containers/Hashing.hpp"
#include "Containers/HashMap.hpp"
#include "Containers/HashSet.hpp"
#include "Containers/SlotMap.hpp"
#include "Memory/Block.hpp"
#include "Memory/Graph.hpp"
#include "Memory/Heap.hpp"
#include "Memory/LocalStackAllocator.hpp"
#include "Memory/Memory.hpp"
#include "Memory/Pool.hpp"
#include "Memory/Stack.hpp"
#include "Memory/ZeroAllocator.hpp"
#include "String/Rune.hpp"
#include "String/String.hpp"
#include "String/FixedString.hpp"
#include "String/CharacterTraits.hpp"
#include "String/StringRange.hpp"
#include "String/StringBuilder.hpp"
#include "String/StringConversion.hpp"
#include "String/StringUtility.hpp"
#include "String/ToString.hpp"
#include "Containers/BitStream.hpp"
#include "Regex/Regex.hpp"
#include "Utility/BitField.hpp"
#include "Utility/ByteEnum.hpp"
#include "Utility/ConditionalRange.hpp"
#include "Utility/EnumDeclaration.hpp"
#include "Utility/Guid.hpp"
#include "Utility/IdSequence.hpp"
#include "Utility/TextStream.hpp"
#include "Utility/HalfFloat.hpp"
#include "Utility/MaxSizeof.hpp"
#include "VirtualAny.hpp"
#include "Utility/IdStore.hpp"
#include "Utility/ItemCache.hpp"
#include "Utility/Log2.hpp"
#include "Utility/Status.hpp"
#include "Utility/ForEachRange.hpp"
#include "Utility/Misc.hpp"
#include "Utility/Standard.hpp"
#include "Utility/Typedefs.hpp"
#include "Utility/UintN.hpp"
#include "Utility/UniquePointer.hpp"
#include "Utility/Functor.hpp"
#include "Utility/HalfFloat.hpp"
#include "Utility/Callback.hpp"
#include "Utility/PointerCast.hpp"
#include "Lexer/Lexer.hpp"
#include "Utility/Guid.hpp"
#include "Utility/NativeType.hpp"
#include "Utility/Variant.hpp"
#include "Utility/Determinism.hpp"
#include "Utility/SpinLock.hpp"
#include "Utility/Web.hpp"
#include "Singleton.hpp"

namespace Math
{
#include "Utility/Typedefs.hpp"
}// namespace Math

#include "Math/Reals.hpp"
#include "Math/MatrixStorage.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix2.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Matrix4.hpp"
#include "Math/IntVector2.hpp"
#include "Math/IntVector3.hpp"
#include "Math/IntVector4.hpp"
#include "Math/BoolVector2.hpp"
#include "Math/BoolVector3.hpp"
#include "Math/BoolVector4.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Math.hpp"
#include "Math/SharedVectorFunctions.hpp"

#include "Math/Random.hpp"
#include "Math/ByteColor.hpp"
#include "Math/Curve.hpp"
#include "Math/DecomposedMatrix4.hpp"
#include "Math/EulerOrder.hpp"
#include "Math/EulerAngles.hpp"
#include "Math/Numerical.hpp"

#include "Math/VectorHashPolicy.hpp"
#include "Math/WeightedProbabilityTable.hpp"

#include "Math/GenericVector.hpp"
#include "Math/ExtendableMath.hpp"
#include "Math/ErrorCallbacks.hpp"
#include "Math/BlockVector3.hpp"
#include "Math/IndexPolicies.hpp"
#include "Math/JacobiSolver.hpp"
#include "Math/ConjugateGradient.hpp"
#include "Math/SimpleCgPolicies.hpp"
#include "Math/GaussSeidelSolver.hpp"

#include "Math/MathToString.hpp"

#include "Math/SimMath.hpp"
#include "Math/SimVectors.hpp"
#include "Math/SimMatrix3.hpp"
#include "Math/SimMatrix4.hpp"
#include "Math/SimConversion.hpp"

namespace Zero
{
#include "Math/BasicNativeTypesMath.inl"
#include "Math/MathImports.hpp"
}

#include "Utility/Rect.hpp"
#include "Utility/Image.hpp"

#include "Platform/PrivateImplementation.hpp"
#include "Platform/Utilities.hpp"
#include "Platform/OsHandle.hpp"
#include "Platform/Thread.hpp"
#include "Platform/ThreadSync.hpp"
#include "Platform/CrashHandler.hpp"
#include "Platform/Debug.hpp"
#include "Platform/DebugSymbolInformation.hpp"
#include "Platform/ExternalLibrary.hpp"
#include "Platform/File.hpp"
#include "Platform/FileEvents.hpp"
#include "Platform/FilePath.hpp"
#include "Platform/FileSystem.hpp"
#include "Platform/FpControl.hpp"
#include "Platform/Lock.hpp"
#include "Platform/Process.hpp"
#include "Platform/Registry.hpp"
#include "Platform/Resolution.hpp"
#include "Platform/SocketEnums.hpp"
#include "Platform/SocketConstants.hpp"
#include "Platform/Socket.hpp"
#include "Platform/IpAddress.hpp"
#include "Platform/Timer.hpp"
#include "Platform/TimerBlock.hpp"
#include "Platform/DirectoryWatcher.hpp"
#include "Platform/Peripherals.hpp"
#include "Platform/ExecutableResource.hpp"
#include "Platform/CommandLineSupport.hpp"
#include "Platform/Shell.hpp"
#include "Platform/ComPort.hpp"
#include "Platform/Intrinsics.hpp"
#include "Platform/Browser.hpp"
#include "Platform/RendererEnumerations.hpp"
#include "Platform/Renderer.hpp"
#include "Platform/Audio.hpp"
