#include "file_dialog.h"

#include <stb_image.h>
#include <sys/stat.h>
#include <windows.h>

#include <algorithm>
#include <fstream>

#undef max

#define ICON_SIZE (ImGui::GetFont()->FontSize + 3)
#define GUI_ELEMENT_SIZE std::max(GImGui->FontSize + 10.f, 24.f)
#define DEFAULT_ICON_SIZE 32
#define PI 3.141592f

bool FolderNode(const char* label, ImTextureID icon, bool& clicked) {
  ImGuiContext& g = *GImGui;
  ImGuiWindow* window = g.CurrentWindow;

  clicked = false;

  ImU32 id = window->GetID(label);
  int opened = window->StateStorage.GetInt(id, 0);
  ImVec2 pos = window->DC.CursorPos;
  const bool is_mouse_x_over_arrow = (g.IO.MousePos.x >= pos.x && g.IO.MousePos.x < pos.x + g.FontSize);
  if (ImGui::InvisibleButton(label, ImVec2(-FLT_MIN, g.FontSize + g.Style.FramePadding.y * 2))) {
    if (is_mouse_x_over_arrow) {
      int* p_opened = window->StateStorage.GetIntRef(id, 0);
      opened = *p_opened = !*p_opened;
    } else {
      clicked = true;
    }
  }
  bool hovered = ImGui::IsItemHovered();
  bool active = ImGui::IsItemActive();
  bool doubleClick = ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left);
  if (doubleClick && hovered) {
    int* p_opened = window->StateStorage.GetIntRef(id, 0);
    opened = *p_opened = !*p_opened;
    clicked = false;
  }
  if (hovered || active)
    window->DrawList->AddRectFilled(
        g.LastItemData.Rect.Min, g.LastItemData.Rect.Max,
        ImGui::ColorConvertFloat4ToU32(
            ImGui::GetStyle().Colors[active ? ImGuiCol_HeaderActive : ImGuiCol_HeaderHovered]));

  float icon_posX = pos.x + g.FontSize + g.Style.FramePadding.y;
  float text_posX = icon_posX + g.Style.FramePadding.y + ICON_SIZE;
  ImGui::RenderArrow(
      window->DrawList, ImVec2(pos.x, pos.y + g.Style.FramePadding.y),
      ImGui::ColorConvertFloat4ToU32(
          ImGui::GetStyle()
              .Colors[((hovered && is_mouse_x_over_arrow) || opened) ? ImGuiCol_Text : ImGuiCol_TextDisabled]),
      opened ? ImGuiDir_Down : ImGuiDir_Right);
  window->DrawList->AddImage(icon, ImVec2(icon_posX, pos.y), ImVec2(icon_posX + ICON_SIZE, pos.y + ICON_SIZE));
  ImGui::RenderText(ImVec2(text_posX, pos.y + g.Style.FramePadding.y), label);
  if (opened) ImGui::TreePush(label);
  return opened != 0;
}

bool FileNode(const char* label, ImTextureID icon) {
  ImGuiContext& g = *GImGui;
  ImGuiWindow* window = g.CurrentWindow;

  ImVec2 pos = window->DC.CursorPos;
  bool ret = ImGui::InvisibleButton(label, ImVec2(-FLT_MIN, g.FontSize + g.Style.FramePadding.y * 2));

  bool hovered = ImGui::IsItemHovered();
  bool active = ImGui::IsItemActive();
  if (hovered || active)
    window->DrawList->AddRectFilled(
        g.LastItemData.Rect.Min, g.LastItemData.Rect.Max,
        ImGui::ColorConvertFloat4ToU32(
            ImGui::GetStyle().Colors[active ? ImGuiCol_HeaderActive : ImGuiCol_HeaderHovered]));

  // Icon, text
  window->DrawList->AddImage(icon, ImVec2(pos.x, pos.y), ImVec2(pos.x + ICON_SIZE, pos.y + ICON_SIZE));
  ImGui::RenderText(ImVec2(pos.x + g.Style.FramePadding.y + ICON_SIZE, pos.y + g.Style.FramePadding.y), label);
  return ret;
}

bool PathBox(const char* label, std::filesystem::path& path, char* path_buffer, ImVec2 size_arg) {
  ImGuiWindow* window = ImGui::GetCurrentWindow();
  if (window->SkipItems) return false;

  bool ret = false;
  const ImGuiID id = window->GetID(label);
  int* state = window->StateStorage.GetIntRef(id, 0);

  ImGui::SameLine();

  ImGuiContext& g = *GImGui;
  const ImGuiStyle& style = g.Style;
  ImVec2 pos = window->DC.CursorPos;
  ImVec2 uiPos = ImGui::GetCursorPos();
  ImVec2 size = ImGui::CalcItemSize(size_arg, 200, GUI_ELEMENT_SIZE);
  const ImRect bb(pos, pos + size);

  // buttons
  if (!(*state & 0b001)) {
    ImGui::PushClipRect(bb.Min, bb.Max, false);

    // background
    bool hovered = g.IO.MousePos.x >= bb.Min.x && g.IO.MousePos.x <= bb.Max.x && g.IO.MousePos.y >= bb.Min.y &&
                   g.IO.MousePos.y <= bb.Max.y;
    bool clicked = hovered && ImGui::IsMouseReleased(ImGuiMouseButton_Left);
    bool any_other_hover_or_clicked = false;  // are any other items hovered or clicked?
    window->DrawList->AddRectFilled(
        pos, pos + size,
        ImGui::ColorConvertFloat4ToU32(
            ImGui::GetStyle().Colors[(*state & 0b10) ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg]));

    // fetch the buttons (so that we can throw some away if needed)
    std::vector<std::string> btn_list;
    float total_width = 0.0f;
    for (auto& comp : path) {
      std::string section = comp.u8string();
      if (section.size() == 1 && (section[0] == '\\' || section[0] == '/')) continue;

      total_width += ImGui::CalcTextSize(section.c_str()).x + style.FramePadding.x * 2.0f + GUI_ELEMENT_SIZE;
      btn_list.push_back(section);
    }
    total_width -= GUI_ELEMENT_SIZE;

    // UI buttons
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, ImGui::GetStyle().ItemSpacing.y));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    bool is_first_element = true;
    for (size_t i = 0; i < btn_list.size(); i++) {
      if (total_width > size.x - 30 && i != btn_list.size() - 1) {  // trim some buttons if there's not enough space
        float elSize = ImGui::CalcTextSize(btn_list[i].c_str()).x + style.FramePadding.x * 2.0f + GUI_ELEMENT_SIZE;
        total_width -= elSize;
        continue;
      }

      ImGui::PushID(static_cast<int>(i));
      if (!is_first_element) {
        ImGui::ArrowButtonEx("##dir_dropdown", ImGuiDir_Right, ImVec2(GUI_ELEMENT_SIZE, GUI_ELEMENT_SIZE));
        any_other_hover_or_clicked |= ImGui::IsItemHovered() | ImGui::IsItemClicked();
        ImGui::SameLine();
      }
      if (ImGui::Button(btn_list[i].c_str(), ImVec2(0, GUI_ELEMENT_SIZE))) {
        std::string new_path = "";
        for (size_t j = 0; j <= i; j++) {
          new_path += btn_list[j];
          if (j != i) new_path += "\\";
        }
        path = std::filesystem::u8path(new_path);
        ret = true;
      }
      any_other_hover_or_clicked |= ImGui::IsItemHovered() | ImGui::IsItemClicked();
      ImGui::SameLine();
      ImGui::PopID();

      is_first_element = false;
    }
    ImGui::PopStyleVar(2);

    // click state
    if (!any_other_hover_or_clicked && clicked) {
      strcpy(path_buffer, path.u8string().c_str());
      *state |= 0b001;
      *state &= 0b011;  // remove SetKeyboardFocus flag
    } else
      *state &= 0b110;

    // hover state
    if (!any_other_hover_or_clicked && hovered && !clicked)
      *state |= 0b010;
    else
      *state &= 0b101;

    ImGui::PopClipRect();

    // allocate space
    ImGui::SetCursorPos(uiPos);
    ImGui::ItemSize(size);
  }
  // input box
  else {
    bool skip_active_check = false;
    if (!(*state & 0b100)) {
      skip_active_check = true;
      ImGui::SetKeyboardFocusHere();
      if (!ImGui::IsMouseClicked(ImGuiMouseButton_Left)) *state |= 0b100;
    }
    if (ImGui::InputTextEx("##pathbox_input", "", path_buffer, 1024, size_arg, ImGuiInputTextFlags_EnterReturnsTrue)) {
      std::string temp_str(path_buffer);
      if (std::filesystem::exists(temp_str)) path = std::filesystem::u8path(temp_str);
      ret = true;
    }
    if (!skip_active_check && !ImGui::IsItemActive()) *state &= 0b010;
  }

  return ret;
}

bool FileIcon(const char* label, bool is_selected, std::shared_ptr<genesis::Texture2D> icon, ImVec2 size,
              bool has_preview) {
  ImGuiStyle& style = ImGui::GetStyle();
  ImGuiContext& g = *GImGui;
  ImGuiWindow* window = g.CurrentWindow;

  float window_space = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
  ImVec2 pos = window->DC.CursorPos;
  bool ret = false;

  if (ImGui::InvisibleButton(label, size)) ret = true;

  bool hovered = ImGui::IsItemHovered();
  bool active = ImGui::IsItemActive();
  bool double_click = ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left);
  if (double_click && hovered) ret = true;

  float icon_size = size.y - g.FontSize * 2;
  float icon_pos_x = pos.x + (size.x - icon_size) / 2.0f;
  ImVec2 textSize = ImGui::CalcTextSize(label, 0, true, size.x);

  if (hovered || active || is_selected)
    window->DrawList->AddRectFilled(
        g.LastItemData.Rect.Min, g.LastItemData.Rect.Max,
        ImGui::ColorConvertFloat4ToU32(
            ImGui::GetStyle()
                .Colors[active ? ImGuiCol_HeaderActive : (is_selected ? ImGuiCol_Header : ImGuiCol_HeaderHovered)]));

  if (has_preview) {
    ImVec2 availSize = ImVec2(size.x, icon_size);

    float scale = std::min<float>(availSize.x / icon->GetWidth(), availSize.y / icon->GetHeight());
    availSize.x = icon->GetWidth() * scale;
    availSize.y = icon->GetHeight() * scale;

    float previewPosX = pos.x + (size.x - availSize.x) / 2.0f;
    float previewPosY = pos.y + (icon_size - availSize.y) / 2.0f;

    window->DrawList->AddImage((ImTextureID)icon->GetID(), ImVec2(previewPosX, previewPosY),
                               ImVec2(previewPosX + availSize.x, previewPosY + availSize.y));
  } else
    window->DrawList->AddImage((ImTextureID)icon->GetID(), ImVec2(icon_pos_x, pos.y),
                               ImVec2(icon_pos_x + icon_size, pos.y + icon_size));

  window->DrawList->AddText(g.Font, g.FontSize, ImVec2(pos.x + (size.x - textSize.x) / 2.0f, pos.y + icon_size),
                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]), label, 0, size.x);

  float last_buttom_pos = ImGui::GetItemRectMax().x;
  float this_button_pos =
      last_buttom_pos + style.ItemSpacing.x + size.x;  // Expected position if next button was on same line
  if (this_button_pos < window_space) ImGui::SameLine();

  return ret;
}

FileDialog::FileData::FileData(const std::filesystem::path& path) : path(path) {
  std::error_code ec;
  is_directory = std::filesystem::is_directory(path, ec);
  size = std::filesystem::file_size(path, ec);

  struct stat attr;
  stat(path.u8string().c_str(), &attr);
  date_modified = attr.st_ctime;
}

FileDialog::FileDialog() {
  is_open_ = false;
  type_ = DialogType::kReadDirectory;
  sort_column_ = 0;
  sort_direction_ = ImGuiSortDirection_Ascending;
  filter_selection_index_ = 0;
  input_textbox_[0] = 0;
  path_buffer_[0] = 0;
  search_buffer_[0] = 0;
  new_entry_buffer_[0] = 0;
  selected_file_item_ = -1;
  zoom_ = 1.0f;

  preview_loader_ = nullptr;
  preview_loader_running_ = false;

  SetDirectory(std::filesystem::current_path(), false);

  // favorites are available on every OS
  FileTreeNode* quick_access = new FileTreeNode("Quick Access");
  quick_access->read = true;
  tree_cache_.push_back(quick_access);

  wchar_t username[256] = {0};
  DWORD username_len = 256;
  GetUserNameW(username, &username_len);
  std::wstring user_path = L"C:\\Users\\" + std::wstring(username) + L"\\";

  // Quick Access
  quick_access->children.push_back(new FileTreeNode(user_path + L"Desktop"));
  quick_access->children.push_back(new FileTreeNode(user_path + L"Documents"));
  quick_access->children.push_back(new FileTreeNode(user_path + L"Downloads"));
  quick_access->children.push_back(new FileTreeNode(user_path + L"Pictures"));

  // This PC
  FileTreeNode* this_pc = new FileTreeNode("This PC");
  this_pc->read = true;
  this_pc->children.push_back(new FileTreeNode(user_path + L"Desktop"));
  this_pc->children.push_back(new FileTreeNode(user_path + L"Documents"));
  this_pc->children.push_back(new FileTreeNode(user_path + L"Downloads"));
  this_pc->children.push_back(new FileTreeNode(user_path + L"Music"));
  this_pc->children.push_back(new FileTreeNode(user_path + L"Pictures"));
  this_pc->children.push_back(new FileTreeNode(user_path + L"Videos"));
  DWORD d = GetLogicalDrives();
  for (int i = 0; i < 26; i++)
    if (d & (1 << i)) this_pc->children.push_back(new FileTreeNode(std::string(1, 'A' + i) + ":"));
  tree_cache_.push_back(this_pc);
}
FileDialog::~FileDialog() {
  ClearPreviewIcon();
  ClearIcons();

  for (auto fn : tree_cache_) ClearTree(fn);
  tree_cache_.clear();
}
bool FileDialog::Save(const std::string& key, const std::string& title, const std::string& filter,
                      const std::string& starting_dir) {
  if (!current_key_.empty()) return false;

  current_key_ = key;
  current_title_ = title + "###" + key;
  type_ = DialogType::kSave;

  is_open_ = true;
  result_.clear();
  input_textbox_[0] = 0;
  selections_.clear();
  selected_file_item_ = -1;
  is_multiselect_ = false;

  ParseFilter(filter);
  if (!starting_dir.empty())
    SetDirectory(std::filesystem::u8path(starting_dir), false);
  else
    SetDirectory(current_directory_, false);  // refresh contents

  ImGui::OpenPopup(current_title_.c_str());
  return true;
}
bool FileDialog::Open(const std::string& key, const std::string& title, const std::string& filter, bool is_multiselect,
                      const std::string& starting_dir) {
  if (!current_key_.empty()) {
    return false;
  }

  current_key_ = key;
  current_title_ = title + "###" + key;
  type_ = filter.empty() ? DialogType::kReadDirectory : DialogType::kReadFile;

  is_open_ = true;
  result_.clear();
  input_textbox_[0] = 0;
  selections_.clear();
  selected_file_item_ = -1;
  is_multiselect_ = is_multiselect;

  ParseFilter(filter);
  if (!starting_dir.empty())
    SetDirectory(std::filesystem::u8path(starting_dir), false);
  else
    SetDirectory(current_directory_, false);  // refresh contents

  ImGui::OpenPopup(current_title_.c_str());
  return true;
}
bool FileDialog::IsDone(const std::string& key) {
  bool is_me = current_key_ == key;

  if (is_me && is_open_) {
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
    if (ImGui::BeginPopupModal(current_title_.c_str(), &is_open_, ImGuiWindowFlags_NoScrollbar)) {
      RenderFileDialog();
      ImGui::EndPopup();
    } else {
      is_open_ = false;
    }
  }

  return is_me && !is_open_;
}
void FileDialog::Close() {
  current_key_.clear();
  back_history_ = std::stack<std::filesystem::path>();
  forward_history_ = std::stack<std::filesystem::path>();

  // clear the tree
  for (auto fn : tree_cache_) {
    for (auto item : fn->children) {
      for (auto ch : item->children) ClearTree(ch);
      item->children.clear();
      item->read = false;
    }
  }

  // free icon textures
  ClearPreviewIcon();
  ClearIcons();
}
void FileDialog::Select(const std::filesystem::path& path, bool is_ctrl_down) {
  bool multiselect = is_ctrl_down && is_multiselect_;

  if (!multiselect) {
    selections_.clear();
    selections_.push_back(path);
  } else {
    auto it = std::find(selections_.begin(), selections_.end(), path);
    if (it != selections_.end())
      selections_.erase(it);
    else
      selections_.push_back(path);
  }

  if (selections_.size() == 1) {
    std::string filename = selections_[0].filename().u8string();
    if (filename.size() == 0) {
      filename = selections_[0].u8string();  // drive
    }

    strcpy(input_textbox_, filename.c_str());
  } else {
    std::string textbox_val = "";
    for (const auto& sel : selections_) {
      std::string filename = sel.filename().u8string();
      if (filename.size() == 0) filename = sel.u8string();

      textbox_val += "\"" + filename + "\", ";
    }
    strcpy(input_textbox_, textbox_val.substr(0, textbox_val.size() - 2).c_str());
  }
}
bool FileDialog::Finalize(const std::string& filename) {
  bool has_result = (!filename.empty() && type_ != DialogType::kReadDirectory) || type_ == DialogType::kReadDirectory;

  if (has_result) {
    if (!is_multiselect_ || selections_.size() <= 1) {
      std::filesystem::path path = std::filesystem::u8path(filename);
      if (path.is_absolute())
        result_.push_back(path);
      else
        result_.push_back(current_directory_ / path);
      if (type_ == DialogType::kReadDirectory || type_ == DialogType::kReadFile) {
        if (!std::filesystem::exists(result_.back())) {
          result_.clear();
          return false;
        }
      }
    } else {
      for (const auto& sel : selections_) {
        if (sel.is_absolute())
          result_.push_back(sel);
        else
          result_.push_back(current_directory_ / sel);
        if (type_ == DialogType::kReadDirectory || type_ == DialogType::kReadFile) {
          if (!std::filesystem::exists(result_.back())) {
            result_.clear();
            return false;
          }
        }
      }
    }

    if (type_ == DialogType::kSave) {
      // add the extension
      if (filter_selection_index_ < filter_extensions_.size() &&
          filter_extensions_[filter_selection_index_].size() > 0) {
        if (!result_.back().has_extension()) {
          std::string extAdd = filter_extensions_[filter_selection_index_][0];
          result_.back().replace_extension(extAdd);
        }
      }
    }
  }

  is_open_ = false;

  return true;
}
void FileDialog::ParseFilter(const std::string& filter) {
  filter_ = "";
  filter_extensions_.clear();
  filter_selection_index_ = 0;

  if (filter.empty()) {
    return;
  }

  std::vector<std::string> exts;

  size_t last_split = 0, last_ext = 0;
  bool in_ext_list = false;
  for (size_t i = 0; i < filter.size(); i++) {
    if (filter[i] == ',') {
      if (!in_ext_list)
        last_split = i + 1;
      else {
        exts.push_back(filter.substr(last_ext, i - last_ext));
        last_ext = i + 1;
      }
    } else if (filter[i] == '{') {
      std::string filter_name = filter.substr(last_split, i - last_split);
      if (filter_name == ".*") {
        filter_ += std::string(std::string("All Files (*.*)\0").c_str(), 16);
        filter_extensions_.push_back(std::vector<std::string>());
      } else
        filter_ += std::string((filter_name + "\0").c_str(), filter_name.size() + 1);
      in_ext_list = true;
      last_ext = i + 1;
    } else if (filter[i] == '}') {
      exts.push_back(filter.substr(last_ext, i - last_ext));
      filter_extensions_.push_back(exts);
      exts.clear();

      in_ext_list = false;
    }
  }
  if (last_split != 0) {
    std::string filter_name = filter.substr(last_split);
    if (filter_name == ".*") {
      filter_ += std::string(std::string("All Files (*.*)\0").c_str(), 16);
      filter_extensions_.push_back(std::vector<std::string>());
    } else
      filter_ += std::string((filter_name + "\0").c_str(), filter_name.size() + 1);
  }
}
std::shared_ptr<genesis::Texture2D> FileDialog::GetIcon(const std::filesystem::path& path) {
  if (icons_.count(path) > 0) {
    return icons_[path];
  }

  std::error_code ec;
  icons_[path] = nullptr;

  DWORD attrs = 0;
  UINT flags = SHGFI_ICON | SHGFI_LARGEICON;
  if (!std::filesystem::exists(path, ec)) {
    flags |= SHGFI_USEFILEATTRIBUTES;
    attrs = FILE_ATTRIBUTE_DIRECTORY;
  }

  SHFILEINFOW file_info = {0};
  std::wstring path_w = path.wstring();
  for (int i = 0; i < path_w.size(); i++)
    if (path_w[i] == '/') path_w[i] = '\\';
  SHGetFileInfoW(path_w.c_str(), attrs, &file_info, sizeof(SHFILEINFOW), flags);

  if (file_info.hIcon == nullptr) return nullptr;

  // check if icon is already loaded
  auto itr = std::find(icon_indices_.begin(), icon_indices_.end(), file_info.iIcon);
  if (itr != icon_indices_.end()) {
    const auto& existing_icon_filepath = icon_file_paths_[itr - icon_indices_.begin()];
    icons_[path] = icons_[existing_icon_filepath];
    return icons_[path];
  }

  icon_indices_.push_back(file_info.iIcon);
  icon_file_paths_.push_back(path);

  ICONINFO icon_info = {0};
  GetIconInfo(file_info.hIcon, &icon_info);

  if (icon_info.hbmColor == nullptr) return nullptr;

  DIBSECTION ds;
  GetObject(icon_info.hbmColor, sizeof(ds), &ds);
  int byte_size = ds.dsBm.bmWidth * ds.dsBm.bmHeight * (ds.dsBm.bmBitsPixel / 8);

  if (byte_size == 0) return nullptr;

  uint8_t* data = (uint8_t*)malloc(byte_size);
  GetBitmapBits(icon_info.hbmColor, byte_size, data);

  icons_[path] = genesis::Texture2D::Create((unsigned char*)data, 4, ds.dsBm.bmWidth, ds.dsBm.bmHeight);

  free(data);

  return icons_[path];
}
void FileDialog::ClearIcons() {
  std::vector<std::shared_ptr<genesis::Texture2D>> deleted_icons;

  // delete textures
  for (auto& icon : icons_) {
    if (std::count(deleted_icons.begin(), deleted_icons.end(),
                   icon.second))  // skip duplicates
      continue;

    deleted_icons.push_back(icon.second);
    icon.second = nullptr;
  }
  icon_file_paths_.clear();
  icon_indices_.clear();
  icons_.clear();
}
void FileDialog::RefreshPreviewIcon() {
  if (zoom_ >= 5.0f) {
    if (preview_loader_ == nullptr) {
      preview_loader_running_ = true;
      preview_loader_ = new std::thread(&FileDialog::LoadPreviewIcon, this);
    }
  } else {
    ClearPreviewIcon();
  }
}
void FileDialog::ClearPreviewIcon() {
  StopPreviewIconLoader();

  for (auto& file_data : content_) {
    if (!file_data.has_icon_preview) continue;

    file_data.has_icon_preview = false;
    file_data.icon_preview = nullptr;
  }
}
void FileDialog::StopPreviewIconLoader() {
  if (preview_loader_ != nullptr) {
    preview_loader_running_ = false;

    // wait thread finish
    if (preview_loader_ && preview_loader_->joinable()) preview_loader_->join();

    delete preview_loader_;
    preview_loader_ = nullptr;
  }
}
void FileDialog::LoadPreviewIcon() {
  for (size_t i = 0; preview_loader_running_ && i < content_.size(); i++) {
    auto& data = content_[i];

    if (data.has_icon_preview) {
      continue;
    }

    if (data.path.has_extension()) {
      std::string ext = data.path.extension().u8string();
      if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp" || ext == ".tga") {
        int width, height, nrChannels;
        unsigned char* image = stbi_load(data.path.u8string().c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

        if (image == nullptr || width == 0 || height == 0) continue;

        data.has_icon_preview = true;
        data.icon_preview_data = image;
        data.icon_preview_width = width;
        data.icon_preview_height = height;
      }
    }
  }
  preview_loader_running_ = false;
}
void FileDialog::ClearTree(FileTreeNode* node) {
  if (node == nullptr) return;

  for (auto n : node->children) {
    ClearTree(n);
  }

  delete node;
  node = nullptr;
}
void FileDialog::SetDirectory(const std::filesystem::path& path, bool addHistory) {
  bool is_same_dir = current_directory_ == path;

  if (addHistory && !is_same_dir) {
    back_history_.push(current_directory_);
  }

  current_directory_ = path;
  // drives don't work well without the backslash symbol
  if (path.u8string().size() == 2 && path.u8string()[1] == ':')
    current_directory_ = std::filesystem::u8path(path.u8string() + "\\");

  ClearPreviewIcon();
  content_.clear();  // p == "" after this line, due to reference
  selected_file_item_ = -1;

  if (type_ == DialogType::kReadDirectory || type_ == DialogType::kReadFile) input_textbox_[0] = 0;
  selections_.clear();

  if (!is_same_dir) {
    search_buffer_[0] = 0;
    ClearIcons();
  }

  if (path.u8string() == "Quick Access") {
    for (auto& node : tree_cache_) {
      if (node->path == path)
        for (auto& c : node->children) content_.push_back(FileData(c->path));
    }
  } else if (path.u8string() == "This PC") {
    for (auto& node : tree_cache_) {
      if (node->path == path)
        for (auto& c : node->children) content_.push_back(FileData(c->path));
    }
  } else {
    std::error_code ec;
    if (std::filesystem::exists(current_directory_, ec))
      for (const auto& entry : std::filesystem::directory_iterator(current_directory_, ec)) {
        FileData info(entry.path());

        // skip files when IFD_DIALOG_DIRECTORY
        if (!info.is_directory && type_ == DialogType::kReadDirectory) continue;

        // check if filename matches search query
        if (search_buffer_[0]) {
          std::string filename = info.path.u8string();

          std::string filename_search = filename;
          std::string query(search_buffer_);
          std::transform(filename_search.begin(), filename_search.end(), filename_search.begin(), ::tolower);
          std::transform(query.begin(), query.end(), query.begin(), ::tolower);

          if (filename_search.find(query, 0) == std::string::npos) continue;
        }

        // check if extension matches
        if (!info.is_directory && type_ != DialogType::kReadDirectory) {
          if (filter_selection_index_ < filter_extensions_.size()) {
            const auto& exts = filter_extensions_[filter_selection_index_];
            if (exts.size() > 0) {
              std::string extension = info.path.extension().u8string();

              // extension not found? skip
              if (std::count(exts.begin(), exts.end(), extension) == 0) continue;
            }
          }
        }

        content_.push_back(info);
      }
  }

  SortContent(sort_column_, sort_direction_);
  RefreshPreviewIcon();
}
void FileDialog::SortContent(unsigned int column, unsigned int direction) {
  // 0 -> name, 1 -> date, 2 -> size
  // split into directories and files
  std::partition(content_.begin(), content_.end(), [](const FileData& data) { return data.is_directory; });

  if (content_.size() > 0) {
    // find where the file list starts
    size_t file_index = 0;
    for (; file_index < content_.size(); file_index++)
      if (!content_[file_index].is_directory) break;

    // compare function
    auto compare_fn = [column, direction](const FileData& left, const FileData& right) -> bool {
      // name
      if (column == 0) {
        std::string l_name = left.path.u8string();
        std::string r_name = right.path.u8string();

        std::transform(l_name.begin(), l_name.end(), l_name.begin(), ::tolower);
        std::transform(r_name.begin(), r_name.end(), r_name.begin(), ::tolower);

        int comp = l_name.compare(r_name);

        if (direction == ImGuiSortDirection_Ascending) {
          return comp < 0;
        }
        return comp > 0;
      }
      // date
      else if (column == 1) {
        if (direction == ImGuiSortDirection_Ascending)
          return left.date_modified < right.date_modified;
        else
          return left.date_modified > right.date_modified;
      }
      // size
      else if (column == 2) {
        if (direction == ImGuiSortDirection_Ascending)
          return left.size < right.size;
        else
          return left.size > right.size;
      }
      return false;
    };

    // sort the directories
    std::sort(content_.begin(), content_.begin() + file_index, compare_fn);

    // sort the files
    std::sort(content_.begin() + file_index, content_.end(), compare_fn);
  }
}
void FileDialog::RenderTree(FileTreeNode* node) {
  // directory
  std::error_code ec;
  ImGui::PushID(node);
  bool is_clicked = false;
  std::string display_name = node->path.stem().u8string();
  if (display_name.size() == 0) display_name = node->path.u8string();
  if (FolderNode(display_name.c_str(), (ImTextureID)GetIcon(node->path)->GetID(), is_clicked)) {
    if (!node->read) {
      // cache children if it's not already cached
      if (std::filesystem::exists(node->path, ec))
        for (const auto& entry : std::filesystem::directory_iterator(node->path, ec)) {
          if (std::filesystem::is_directory(entry, ec))
            node->children.push_back(new FileTreeNode(entry.path().u8string()));
        }
      node->read = true;
    }

    // display children
    for (auto c : node->children) RenderTree(c);

    ImGui::TreePop();
  }
  if (is_clicked) SetDirectory(node->path);
  ImGui::PopID();
}
void FileDialog::RenderContent() {
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
    selected_file_item_ = -1;
  }

  // table view
  if (zoom_ == 1.0f) {
    if (ImGui::BeginTable("##contentTable", 3,
                          /*ImGuiTableFlags_Resizable |*/ ImGuiTableFlags_Sortable, ImVec2(0, -FLT_MIN))) {
      // header
      ImGui::TableSetupColumn("Name##filename", ImGuiTableColumnFlags_WidthStretch, 0.0f - 1.0f, 0);
      ImGui::TableSetupColumn("Date modified##filedate",
                              ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 0.0f, 1);
      ImGui::TableSetupColumn("Size##filesize", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 0.0f,
                              2);
      ImGui::TableSetupScrollFreeze(0, 1);
      ImGui::TableHeadersRow();

      // sort
      if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()) {
        if (sort_specs->SpecsDirty) {
          sort_specs->SpecsDirty = false;
          SortContent(sort_specs->Specs->ColumnUserID, sort_specs->Specs->SortDirection);
        }
      }

      // content
      int file_id = 0;
      for (auto& entry : content_) {
        std::string filename = entry.path.filename().u8string();
        if (filename.size() == 0) filename = entry.path.u8string();  // drive

        bool is_selected = std::count(selections_.begin(), selections_.end(), entry.path);

        ImGui::TableNextRow();

        // file name
        ImGui::TableSetColumnIndex(0);
        ImGui::Image((ImTextureID)GetIcon(entry.path)->GetID(), ImVec2(ICON_SIZE, ICON_SIZE));
        ImGui::SameLine();
        if (ImGui::Selectable(filename.c_str(), is_selected,
                              ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick)) {
          std::error_code ec;
          bool is_dir = std::filesystem::is_directory(entry.path, ec);

          if (ImGui::IsMouseDoubleClicked(0)) {
            if (is_dir) {
              SetDirectory(entry.path);
              break;
            } else
              Finalize(filename);
          } else {
            if ((is_dir && type_ == DialogType::kReadDirectory) || !is_dir) Select(entry.path, ImGui::GetIO().KeyCtrl);
          }
        }
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) selected_file_item_ = file_id;
        file_id++;

        // date
        ImGui::TableSetColumnIndex(1);
        auto tm = std::localtime(&entry.date_modified);
        if (tm != nullptr)
          ImGui::Text("%d/%d/%d %02d:%02d", tm->tm_mon + 1, tm->tm_mday, 1900 + tm->tm_year, tm->tm_hour, tm->tm_min);
        else
          ImGui::Text("---");

        // size
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("%.3f KiB", entry.size / 1024.0f);
      }

      ImGui::EndTable();
    }
  } else {
    // content
    int fileId = 0;
    for (auto& entry : content_) {
      if (entry.has_icon_preview && entry.icon_preview_data != nullptr) {
        entry.icon_preview =
            genesis::Texture2D::Create(entry.icon_preview_data, 4, entry.icon_preview_width, entry.icon_preview_height);
        stbi_image_free(entry.icon_preview_data);
        entry.icon_preview_data = nullptr;
      }
      std::string filename = entry.path.filename().u8string();
      if (filename.size() == 0) filename = entry.path.u8string();  // drive

      bool is_selected = std::count(selections_.begin(), selections_.end(), entry.path);

      if (FileIcon(filename.c_str(), is_selected, entry.has_icon_preview ? entry.icon_preview : GetIcon(entry.path),
                   ImVec2(32 + 16 * zoom_, 32 + 16 * zoom_), entry.has_icon_preview)) {
        std::error_code ec;
        bool isDir = std::filesystem::is_directory(entry.path, ec);

        if (ImGui::IsMouseDoubleClicked(0)) {
          if (isDir) {
            SetDirectory(entry.path);
            break;
          } else
            Finalize(filename);
        } else {
          if ((isDir && type_ == DialogType::kReadDirectory) || !isDir) Select(entry.path, ImGui::GetIO().KeyCtrl);
        }
      }
      if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) selected_file_item_ = fileId;
      fileId++;
    }
  }
}

void FileDialog::RenderPopups() {
  bool open_are_you_sure_dlg = false, open_new_file_dlg = false, open_new_directory_dlg = false;
  if (ImGui::BeginPopupContextItem("##dir_context")) {
    if (ImGui::Selectable("New file")) open_new_file_dlg = true;
    if (ImGui::Selectable("New directory")) open_new_directory_dlg = true;
    if (selected_file_item_ != -1 && ImGui::Selectable("Delete")) open_are_you_sure_dlg = true;
    ImGui::EndPopup();
  }
  if (open_are_you_sure_dlg) ImGui::OpenPopup("Are you sure?##delete");
  if (open_new_file_dlg) ImGui::OpenPopup("Enter file name##newfile");
  if (open_new_directory_dlg) ImGui::OpenPopup("Enter directory name##newdir");
  if (ImGui::BeginPopupModal("Are you sure?##delete")) {
    if (selected_file_item_ >= static_cast<int>(content_.size()) || content_.size() == 0)
      ImGui::CloseCurrentPopup();
    else {
      const FileData& data = content_[selected_file_item_];
      ImGui::TextWrapped("Are you sure you want to delete %s?", data.path.filename().u8string().c_str());
      if (ImGui::Button("Yes")) {
        std::error_code ec;
        std::filesystem::remove_all(data.path, ec);
        SetDirectory(current_directory_, false);  // refresh
        ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button("No")) ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
  if (ImGui::BeginPopupModal("Enter file name##newfile")) {
    ImGui::PushItemWidth(250.0f);
    ImGui::InputText("##newfilename", new_entry_buffer_,
                     1024);  // TODO: remove hardcoded literals
    ImGui::PopItemWidth();

    if (ImGui::Button("OK")) {
      std::ofstream out((current_directory_ / std::string(new_entry_buffer_)).string());
      out << "";
      out.close();

      SetDirectory(current_directory_, false);  // refresh
      new_entry_buffer_[0] = 0;

      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
      new_entry_buffer_[0] = 0;
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
  if (ImGui::BeginPopupModal("Enter directory name##newdir")) {
    ImGui::PushItemWidth(250.0f);
    ImGui::InputText("##newfilename", new_entry_buffer_,
                     1024);  // TODO: remove hardcoded literals
    ImGui::PopItemWidth();

    if (ImGui::Button("OK")) {
      std::error_code ec;
      std::filesystem::create_directory(current_directory_ / std::string(new_entry_buffer_), ec);
      SetDirectory(current_directory_, false);  // refresh
      new_entry_buffer_[0] = 0;
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
      ImGui::CloseCurrentPopup();
      new_entry_buffer_[0] = 0;
    }
    ImGui::EndPopup();
  }
}
void FileDialog::RenderFileDialog() {
  /***** TOP BAR *****/
  bool no_back_history = back_history_.empty(), no_forward_history = forward_history_.empty();

  ImGui::PushStyleColor(ImGuiCol_Button, 0);
  if (no_back_history) ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
  if (ImGui::ArrowButtonEx("##back", ImGuiDir_Left, ImVec2(GUI_ELEMENT_SIZE, GUI_ELEMENT_SIZE),
                           back_history_.empty() * ImGuiItemFlags_Disabled)) {
    std::filesystem::path new_path = back_history_.top();
    back_history_.pop();
    forward_history_.push(current_directory_);

    SetDirectory(new_path, false);
  }
  if (no_back_history) ImGui::PopStyleVar();
  ImGui::SameLine();

  if (no_forward_history) ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
  if (ImGui::ArrowButtonEx("##forward", ImGuiDir_Right, ImVec2(GUI_ELEMENT_SIZE, GUI_ELEMENT_SIZE),
                           forward_history_.empty() * ImGuiItemFlags_Disabled)) {
    std::filesystem::path new_path = forward_history_.top();
    forward_history_.pop();
    back_history_.push(current_directory_);

    SetDirectory(new_path, false);
  }
  if (no_forward_history) ImGui::PopStyleVar();
  ImGui::SameLine();

  if (ImGui::ArrowButtonEx("##up", ImGuiDir_Up, ImVec2(GUI_ELEMENT_SIZE, GUI_ELEMENT_SIZE))) {
    if (current_directory_.has_parent_path()) SetDirectory(current_directory_.parent_path());
  }

  std::filesystem::path cur_dir_copy = current_directory_;
  if (PathBox("##pathbox", cur_dir_copy, path_buffer_, ImVec2(-250, GUI_ELEMENT_SIZE))) SetDirectory(cur_dir_copy);
  ImGui::SameLine();
  ImGui::SameLine();
  ImGui::PopStyleColor();

  if (ImGui::InputTextEx("##searchTB", "Search", search_buffer_, 128, ImVec2(-FLT_MIN, GUI_ELEMENT_SIZE),
                         0))                  // TODO: no hardcoded literals
    SetDirectory(current_directory_, false);  // refresh

  /***** CONTENT *****/
  float bottom_bar_height =
      (GImGui->FontSize + ImGui::GetStyle().FramePadding.y + ImGui::GetStyle().ItemSpacing.y * 2.0f) * 2;
  if (ImGui::BeginTable("##table", 2, ImGuiTableFlags_Resizable, ImVec2(0, -bottom_bar_height))) {
    ImGui::TableSetupColumn("##tree", ImGuiTableColumnFlags_WidthFixed, 125.0f);
    ImGui::TableSetupColumn("##content", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableNextRow();

    // the tree on the left side
    ImGui::TableSetColumnIndex(0);
    ImGui::BeginChild("##treeContainer", ImVec2(0, -bottom_bar_height));
    for (auto node : tree_cache_) RenderTree(node);
    ImGui::EndChild();

    // content on the right side
    ImGui::TableSetColumnIndex(1);
    ImGui::BeginChild("##contentContainer", ImVec2(0, -bottom_bar_height));
    RenderContent();
    ImGui::EndChild();
    if (ImGui::IsItemHovered() && ImGui::GetIO().KeyCtrl && ImGui::GetIO().MouseWheel != 0.0f) {
      SetZoom(zoom_ + ImGui::GetIO().MouseWheel);
    }

    // New file, New directory and Delete popups
    RenderPopups();

    ImGui::EndTable();
  }

  /***** BOTTOM BAR *****/
  ImGui::Text("File name:");
  ImGui::SameLine();
  if (ImGui::InputTextEx("##file_input", "Filename", input_textbox_, 1024,
                         ImVec2((type_ != DialogType::kReadDirectory) ? -250.0f : -FLT_MIN, 0),
                         ImGuiInputTextFlags_EnterReturnsTrue)) {
    bool success = Finalize(std::string(input_textbox_));

    if (!success) MessageBeep(MB_ICONERROR);
  }
  if (type_ != DialogType::kReadDirectory) {
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-FLT_MIN);
    int sel = static_cast<int>(filter_selection_index_);
    if (ImGui::Combo("##ext_combo", &sel, filter_.c_str())) {
      filter_selection_index_ = static_cast<size_t>(sel);
      SetDirectory(current_directory_, false);  // refresh
    }
  }

  // buttons
  float ok_cancel_width = GUI_ELEMENT_SIZE * 7;
  ImGui::SetCursorPosX(ImGui::GetWindowWidth() - ok_cancel_width);
  if (ImGui::Button(type_ == DialogType::kSave ? "Save" : "Open",
                    ImVec2(ok_cancel_width / 2 - ImGui::GetStyle().ItemSpacing.x, 0.0f))) {
    std::string filename(input_textbox_);
    bool success = false;
    if (!filename.empty() || type_ == DialogType::kReadDirectory) success = Finalize(filename);
    if (!success) MessageBeep(MB_ICONERROR);
  }
  ImGui::SameLine();
  if (ImGui::Button("Cancel", ImVec2(-FLT_MIN, 0.0f))) {
    if (type_ == DialogType::kReadDirectory)
      is_open_ = false;
    else
      Finalize();
  }

  int escapeKey = ImGui::GetIO().KeyMap[ImGuiKey_Escape];
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && escapeKey >= 0 &&
      ImGui::IsKeyPressed((ImGuiKey)escapeKey))
    is_open_ = false;
}