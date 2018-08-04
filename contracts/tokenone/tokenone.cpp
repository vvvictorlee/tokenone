/**
 * @brief token contract
 */


#include "tokenone.hpp"

void token::create( account_name issuer, string symbol, string name, uint64_t max_supply, uint8_t decimal){

    require_auth( _self );

    meta_table t( _self, _self);
    eosio_assert( t.find(1) == t.end(), "token already created");

    eosio_assert( symbol.length() <= 8, "symbol length should not greater than 8");
    eosio_assert( all_of(symbol.begin(), symbol.end(), [](char c)->bool { return (c >= 'A' && c <= 'Z')||(c >= '0' && c <= '9'); }),
            "symbol just allowed characters belongs A-Z and 0-9");


    eosio_assert( name.length() <= 20, "token name length should not greater than 20");

    eosio_assert( max_supply > 0, "max-supply must be positive");
    eosio_assert( max_supply <= max_amount, "max_supply exceed the max_amount");

    eosio_assert( decimal <= 16, "precision ${p} should be <= 18");






    t.emplace( _self, [&]( auto& s ) {
        s.id            = 1;
        s.symbol        = symbol;
        s.name          = name;
        s.max_supply    = max_supply;
        s.supply        = 0;
        s.decimal       = decimal;
        s.issuer        = issuer;
    });
}

void token::issue( account_name to, float64_t quantity, string memo ){

}

void token::transfer( account_name from, account_name to, uint64_t quantity, string memo ){

}

void token::approve( account_name owner, account_name spender, uint64_t quantity){
    
}

void token::sub_balance( account_name owner,  uint64_t quantity ) {
    account_table t( _self, _self );
    const auto& from = t.get( owner, "account not found." );
    t.modify( from, owner, [&]( auto& a ) {
        a.balance -= quantity;
    });
}

void token::add_balance( account_name owner,  uint64_t quantity, account_name ram_payer ) {
    account_table t( _self, _self );
    auto to = t.find( owner );
    
    if(to == t.end() ){
        t.emplace( ram_payer, [&]( auto& a ){
            a.name = owner;
            a.balance = quantity;
        });
    } else {
        t.modify( to, 0, [&]( auto& a ) {
            a.balance += quantity;
        });
    }
}

void token::add_apply( uint64_t quantity ){
    
}


EOSIO_ABI( token, (create)(issue)(transfer)(approve) )
