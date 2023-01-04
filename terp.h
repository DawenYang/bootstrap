#include <cstdint>
#include <string>
#include "result.h"

#ifndef BOOTSTRAP_TERP_H
#define BOOTSTRAP_TERP_H

namespace basecode {
    // basecode interpreter, which consumes base IR
    //
    //
    // register-based machine
    // with a generic stack
    //
    // register file:
    //
    // general purpose: data or address
    // I0-I63: integer registers 64-bit
    //
    // data only:
    // F0-F63: floating point registers (double precision)
    //
    // stack pointer: sp (like an IXX register)
    // program counter: pc (can be read, but not changed)
    // flags: fr (definitely read; maybe write)
    // status: sr (definitely read; maybe write)
    //
    //
    // instructions:
    //
    // memory access
    // --------------
    //
    // load{.b|.w|.dw|.qw}
    //                  ^ default
    // .b  = 8-bit
    // .w  = 16-bit
    // .dw = 32-bit
    // .qw = 64-bit
    //
    // non-used bits are zero-extended
    //
    // store{.b|.w|.dw|.qw}
    //
    // non-used bits are zero-extended
    //
    // addressing modes (loads & stores):
    //      {target-register}, [{source-register}]
    //          "      "     , [{source-register}, offset constant]
    //          "      "     , [{source-register}, {offset-register}]
    //          "      "     , {source-register}, post increment constant++
    //          "      "     , {source-register}, post increment register++
    //          "      "     , {source-register}, ++pre increment constant
    //          "      "     , {source-register}, ++pre increment register
    //          "      "     , {source-register}, post decrement constant--
    //          "      "     , {source-register}, post decrement register--
    //          "      "     , {source-register}, --pre decrement constant
    //          "      "     , {source-register}, --pre decrement register
    //
    // copy {source-register}, {target-register}, {length constant}
    // copy {source-register}, {target-register}, {length-register}
    //
    // fill {constant}, {target-register}, {length constant}
    // fill {constant}, {target-register}, {length-register}
    //
    // fill {source-register}, {target-register}, {length constant}
    // fill {source-register}, {target-register}, {length register}
    //
    // register/constant
    // -------------------
    //
    // move{.b|.w|.dw|.qw}  {source constant}, {target register}
    //                      {source register}, {target register}
    //
    // move.b #$06, I3
    // move I3, I16
    //
    // stack
    // --------
    //
    //  push{.b|.w|.dw|.qw}
    //  pop{.b|.w|.dw|.qw}
    //
    //  sp register behaves like IXX register.
    //
    // ALU
    // -----
    //
    //  size applicable to all: {.b|.w|.dw|.qw}
    //
    // add
    // addc
    //
    // sub
    // subc
    //
    // mul
    // div
    // mod
    // neg
    //
    // shr
    // shl
    // ror
    // rol
    //
    // and
    // or
    // xor
    //
    // not
    // bis (bit set)
    // bic (bit clear)
    // test
    //
    // cmp (compare register to register, or register to constant)
    //
    // branch/conditional execution
    // ----------------------------------
    //
    // bz   (branch if zero)
    // bnz  (branch if not-zero)
    //
    // tbz  (test & branch if not set)
    // tbnz (test & branch if set)
    //
    // bne
    // beq
    // bae
    // ba
    // ble
    // bl
    // bo
    // bcc
    // bcs
    //
    // jsr  - equivalent to call (encode tail flag?)
    //          push current PC + sizeof(instruction)
    //          jmp to address
    //
    // ret  - jump to address on stack
    //
    // jmp
    //      - absolute constant: jmp #$ffffffff0
    //      - indirect register: jmp [I4]
    //      - direct: jmp I4
    //
    // nop
    //

    struct register_file_t {
        uint64_t i[64];
        double f[64];
        uint64_t pc;
        uint64_t sp;
        uint64_t fr;
        uint64_t sr;
    };

    enum class opcodes : uint16_t {
        nop = 0,
        load,
        store,
        move,
        push,
        pop,
        add,
        sub,
        mul,
        div,
        mod,
        neg,
        shr,
        shl,
        ror,
        rol,
        and_op,
        or_op,
        xor_op,
        not_op,
        bis,
        bic,
        test,
        cmp,
        bz,
        bnz,
        tbz,
        tbnz,
        bne,
        beq,
        bae,
        ba,
        ble,
        bl,
        bo,
        bcc,
        bcs,
        jsr,
        ret,
        jmp,
        meta,
        debug
    };

    enum class operand_types : uint8_t {
        register_integer,
        register_floating_point,
        register_sp,
        register_pc,
        register_flags,
        register_status,
        constant
    };

    struct operand_encoding_t {
        operand_types type;
        uint8_t index;
        uint64_t value;
    };

    struct instruction_t {
        opcodes op;
        uint8_t operands_count;
        operand_encoding_t operands[4];
    };

    struct debug_information_t {
        uint32_t line_number;
        uint16_t column_number;
        std::string symbol;
        std::string source_file;
    };

    class terp {
    public:
        explicit terp(uint32_t heap_size);

        virtual ~terp();

        uint64_t pop();

        size_t heap_size() const;

        void push(uint64_t value);

        bool initialize(result& r);

        size_t heap_size_in_qwords() const;

        const register_file_t& register_file() const;

    private:
        uint32_t _heap_size = 0;
        uint64_t* _heap = nullptr;
        register_file_t _registers {};
    };

}

#endif //BOOTSTRAP_TERP_H
