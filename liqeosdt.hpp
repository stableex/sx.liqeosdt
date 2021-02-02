#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

namespace liqeosdt {

    using eosio::asset;
    using eosio::name;
    using eosio::multi_index;
    using eosio::extended_symbol;
    using eosio::symbol;

    const extended_symbol EOSDT{ symbol{"EOSDT", 9}, "eosdtsttoken"_n };

    const name id = "eosdtliq"_n;
    const name code = "eosdtliqdatr"_n;
    const std::string description = "EOSDT Liquidator";
    const extended_symbol currency = EOSDT;
    const std::string memo = "";
    const int64_t min_amount = 5'000000000;


    /**
     * parameters table
     */
    struct [[eosio::table]] parameters_row {
        uint64_t    parameter_id;
        asset       surplus_debt;
        asset       bad_debt;
        asset       collat_balance;
        asset       nut_collat_balance;

        uint64_t primary_key() const { return parameter_id; }
    };
    typedef eosio::multi_index< "parameters"_n, parameters_row > parameters;


    std::pair<asset, std::string> get_liquidation_amount() {

        parameters paramstbl( code, code.value );
        for(const auto& row: paramstbl) {
            if(row.bad_debt.amount >= min_amount) return { row.bad_debt, ""};
            if(row.surplus_debt.amount >= min_amount) return { row.surplus_debt, "surplus"};
        }

        return {asset{0, EOSDT.get_symbol()}, ""};
    }

}