//
// Created by vsvood on 9/20/21.
//

#ifndef SQREQUATIONSOLVER_CUSTOM_STATUS_LIB_H
#define SQREQUATIONSOLVER_CUSTOM_STATUS_LIB_H

enum class CustomStatus {
  kOk,
  kWrongInputParams,
  kWrongOutputParams,
  kRuntimeError
};

extern const char *kCustomStatusDescription[];

#endif //SQREQUATIONSOLVER_CUSTOM_STATUS_LIB_H
