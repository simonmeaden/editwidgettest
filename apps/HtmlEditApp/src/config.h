#pragma once

#include "config/baseconfig.h"

class Config : public BaseConfig
{
public:
  explicit Config(QObject* parent = nullptr);
  explicit Config(const QString& filename, QObject* parent = nullptr);

  bool save(const QString& filename = QString());
  bool load(const QString& filename = QString());
};
