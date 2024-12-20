#include "AssetPackagePanel.hpp"
#include "AssetPackage/AssetPackage.hpp"

using namespace AssetPackageTool;

AssetPackagePanel::AssetPackagePanel(nana::window wd, const std::shared_ptr<AssetPackage::AssetPackageFile>& package)
    : nana::panel<false>{ wd }, m_packageFile{ package }
{
}

AssetPackagePanel::~AssetPackagePanel()
{
    m_packageFile = nullptr;
}

void AssetPackagePanel::initialize()
{

}
