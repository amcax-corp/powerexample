#pragma once
#include <App/TransactionObject.h>
#include <Base/Factory.h>

namespace app {

class PFC_APP_API TransactionFactory final : public base::TFactoryBase<TransactionFactory, TransactionObject, base::Type>
{
    friend base::TFactoryBase<TransactionFactory, TransactionObject, base::Type>;

    TransactionFactory() = default;

    public:

    virtual std::unique_ptr<Product> Produce(base::Type const& tag) const override;

    static TransactionFactory& Instance();
};

}  // namespace app