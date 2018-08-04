/**
 * @brief A proposal of standard token contract.
 */

#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/types.hpp>

using std::string;

typedef double float64_t;


class token : public eosio::contract {

private:
    static constexpr uint64_t max_amount = (1LL << 62) - 1;
    static constexpr uint8_t  max_precision = 18;
public:
    token( account_name self ):contract( self ){}

    /// @abi action
    void create( account_name   issuer,
                 string         symbol,
                 string         name,
                 uint64_t       max_supply,
                 uint8_t        decimal);

    /// @abi action
    void issue( account_name    to,
                float64_t       quantity,
                string          memo );

    /// @abi action
    void transfer( account_name from,
                   account_name to,
                   uint64_t     quantity,
                   string       memo );

    /// @abi action
    void approve( account_name  owner,
                  account_name  spender,
                  uint64_t      quantity);

private:
    /// @abi table meta
    struct meta {
        uint64_t        id;
        account_name    issuer;
        string          symbol;
        string          name;
        uint64_t        max_supply;
        uint64_t        supply;
        uint8_t         decimal;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE( meta, (id)(issuer)(symbol)(name)(max_supply)(supply)(decimal))
    };

    typedef eosio::multi_index<N(meta), meta> meta_table;

    /// @abi table account
    struct account {
        account_name    name;
        uint64_t        balance;

        uint64_t primary_key() const { return name; }
        EOSLIB_SERIALIZE( account, (name)(balance))
    };

    typedef eosio::multi_index<N(account), account> account_table;

    /// @abi table allowed
    struct allowed{
        account_name    spender;
        uint64_t        quantity;

        uint64_t primary_key() const { return spender; }
        EOSLIB_SERIALIZE( allowed, (spender)(quantity))
    };

    typedef eosio::multi_index<N(allowed), allowed> allowed_table;

private:
    void sub_balance( account_name owner, uint64_t quantity );
    void add_balance( account_name owner, uint64_t quantity, account_name ram_payer );
    void add_apply( uint64_t quantity );
};

