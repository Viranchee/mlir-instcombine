function(p2_test_nocse name class)
    add_custom_target(${name}-nocse.mlir ALL
            p2 -verbose -no-cse ${CMAKE_CURRENT_SOURCE_DIR}/${name}.mlir ${name}-nocse.mlir
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS p2 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.mlir
            )
    add_custom_target(${name}-nocse.mlir ALL
            llvm-dis-13 ${name}-nocse.mlir
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS p2 ${name}-nocse.mlir
            )
    add_test(NAME Fail-${class}-${name} COMMAND FileCheck-13 --input-file=${CMAKE_CURRENT_BINARY_DIR}/${name}-nocse.mlir ${CMAKE_CURRENT_SOURCE_DIR}/${name}.mlir )
    set_tests_properties(Fail-${class}-${name} PROPERTIES WILL_FAIL TRUE)
endfunction(p2_test_nocse)

function(p2_test name class)
    add_custom_target(${name}-out.mlir ALL
            p2 -verbose ${CMAKE_CURRENT_SOURCE_DIR}/${name}.mlir ${name}-out.mlir
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS p2 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.mlir
    )
    add_custom_target(${name}-out.mlir ALL
            llvm-dis-13 ${name}-out.mlir
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS p2 ${name}-out.mlir
    )
    add_test(NAME ${class}-${name} COMMAND FileCheck-13 --input-file=${CMAKE_CURRENT_BINARY_DIR}/${name}-out.mlir ${CMAKE_CURRENT_SOURCE_DIR}/${name}.mlir )
endfunction(p2_test)

p2_test(cse0 CSEDead)
p2_test(cse1 CSEElim)
p2_test(cse2 CSESimplify)
p2_test(cse3 CSELdElim)
p2_test(cse4 CSEStore2Load)
p2_test(cse5 CSEStElim)
p2_test(cse6 Other)

p2_test_nocse(cse0 CSEDead)
p2_test_nocse(cse1 CSEElim)
p2_test_nocse(cse2 CSESimplify)
p2_test_nocse(cse3 CSELdElim)
p2_test_nocse(cse4 CSEStore2Load)
p2_test_nocse(cse5 CSEStElim)
p2_test_nocse(cse6 Other)

#add_custom_target(cse0-out.mlir ALL
#        p2 ${CMAKE_CURRENT_SOURCE_DIR}/cse0.mlir cse0-out.mlir
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        DEPENDS p2 cse0.mlir
#        )

#add_custom_target(cse0-out.mlir ALL
#        llvm-dis-11 ${CMAKE_CURRENT_BINARY_DIR}/cse0-out.mlir
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        DEPENDS p2 cse0-out.mlir
#        )

#add_test(NAME cse0-check
#         COMMAND FileCheck-11 --input-file=${CMAKE_CURRENT_BINARY_DIR}/cse-out.mlir ${CMAKE_CURRENT_SOURCE_DIR}/cse0.mlir  )
