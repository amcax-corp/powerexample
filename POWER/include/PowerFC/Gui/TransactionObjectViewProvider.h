#ifndef POWERFC_GUI_TRANSACTIONOBJECTVIEWPROVIDER_H
#define POWERFC_GUI_TRANSACTIONOBJECTVIEWPROVIDER_H
#pragma once
#include <App/TransactionObject.h>

namespace gui{
    class TransactionObjectViewProvider: public app::TransactionObject{
        PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

        public:
        TransactionObjectViewProvider();
        ~TransactionObjectViewProvider() override;

        void ApplyNew(app::Document& doc, std::unique_ptr<app::TransactionalObject>&& obj) override;
        void ApplyDelete(app::Document& doc, app::TransactionalObject* obj) override;
    };
}


#endif