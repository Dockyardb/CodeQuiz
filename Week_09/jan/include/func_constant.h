#pragma once

#include <string>
#include "derivable.h"

namespace Function {

  class Constant : public Derivable {
  public:
    Constant(std::string const&);
    virtual ~Constant() = default;

    double eval(double) const override;
    std::string derive() const override;
    std::string print() const override;

  private:
    double value;
  };
}