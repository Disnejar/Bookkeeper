#include "app.h"
#include "imgui.h"
#include "ImFileDialog.h"
//#include "ImGuiDatePicker.hpp"
#include <chrono>

static std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
static tm testTime = *std::gmtime(&currentTime);

void RenderFrame()
{
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("Plik"))
        {
            ImGui::MenuItem("Zapisz");

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    ImGuiWindowFlags flags = 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoSavedSettings;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    if(ImGui::Begin("Tranzakcje", NULL, flags))
    {
        //ImGui::DatePicker("Date and time", testTime);
        if(ImGui::Button("Browse"))
        {
            ifd::FileDialog::Instance().Open("TextureOpenDialog", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
        }

        if (ifd::FileDialog::Instance().IsDone("TextureOpenDialog"))
        {
            if (ifd::FileDialog::Instance().HasResult())
            {
                std::string res = ifd::FileDialog::Instance().GetResult().u8string();
                printf("OPEN[%s]\n", res.c_str());
            }
            ifd::FileDialog::Instance().Close();
        }
        ImGui::End();
    }

    ImGui::ShowDemoWindow();
}