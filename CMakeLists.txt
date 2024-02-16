cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)

project("pass")
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")

find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)


separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})

# include_directories(${PROJECT_SOURCE_DIR}/include)
# include_directories(${PROJECT_BINARY_DIR}/include)

link_directories(${LLVM_BUILD_LIBRARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

llvm_map_components_to_libnames(llvm_libs analysis bitreader bitwriter codegen core asmparser irreader instcombine instrumentation mc objcarcopts scalaropts support ipo target transformutils vectorize)
# # target_link_libraries(Pass 
# #     PRIVATE
# #     MLIRAnalysis
# #     MLIRCallInterfaces
# #     MLIRCastInterfaces
# #     MLIRExecutionEngine
# #     MLIRIR
# #     MLIRLLVMCommonConversion
# #     MLIRLLVMIR
# #     MLIRLLVMToLLVMIRTranslation
# #     MLIRMemRef
# #     MLIRParser
# #     MLIRPass
# #     MLIRSideEffectInterfaces
# #     MLIRSupport
# #     MLIRTargetLLVMIRExport
# #     MLIRTransforms
# #     )

# set(MLIR_COMPONENTS
#     LLVMLinker
#     MLIR_LIBS
#     MLIRAffine
#     MLIRAnalysis
#     MLIRExecutionEngine
#     MLIRIR
#     MLIROptLib 
#     MLIRParser
#     MLIRQuantum 
#     MLIRStandard
#     MLIRSupport
#     MLIRTargetLLVMIR
#     MLIRTransformUtils
# )

# foreach(component ${MLIR_COMPONENTS})
#   list(APPEND MLIR_LIBS "MLIR${component}")
# endforeach()


add_subdirectory(pass)

