#include "config.h"

Config::Config(QObject* parent)
  : BaseConfig{ parent }
{
}

Config::Config(const QString& filename, QObject* parent)
  : BaseConfig{ filename, parent }
{
}

bool
Config::save(const QString& filename)
{
  YAML::Node prefs;
  if (m_rootNode["Preferences"]) {
    prefs = m_rootNode;
  } else {
    m_rootNode["Preferences"] = YAML::Load("{}");
    prefs = m_rootNode["Preferences"];
  }
  for (auto setting : m_settingList) {
    YAML::Node node;
    if (!prefs[setting->id()]) {
      prefs[setting->id()] = YAML::Load("{}");
    }
  }

  BaseConfig::saveFile(filename);
  return true;
}

bool
Config::load(const QString& filename)
{
  BaseConfig::loadFile(filename);
  return true;
}
