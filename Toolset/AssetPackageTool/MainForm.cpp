#include "MainForm.hpp"

using namespace AssetPackageTool;

MainForm::MainForm()
{
    m_place = nullptr;
}

MainForm::~MainForm()
{
    m_place = nullptr;
}

void MainForm::initialize()
{
    m_place = std::make_shared<nana::place>(*this);
    m_place->div("vert<menubar weight=28><tabbar weight=28><tabframe>");

    m_place->collocate();
}
