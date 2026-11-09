// Pairing with the Burstein system when the pairing-allocated bye goes to the
// last player of the sorted list must put that player back into the list for
// the checklist (the iterator used to do it was invalidated by the erase).
void TEST_FUNCTION(const testing::Context &context)
{
  const auto pairing_path =
    context.data_folder_path / (STRINGIFY(TEST_ID) ".output");
  const auto checklist_path =
    context.data_folder_path / (STRINGIFY(TEST_ID) ".checklist.output");
  testing::run(
    context.exe_path.string()
    + " --burstein "
    + (context.data_folder_path / STRINGIFY(TEST_ID) ".input").string()
    + " -p "
    + pairing_path.string()
    + " -l "
    + checklist_path.string());
  std::ifstream stream(checklist_path, std::ios::binary);
  const std::string content{
    std::istreambuf_iterator<char>(stream),
    std::istreambuf_iterator<char>() };
  if (content.find("(bye)") == std::string::npos)
  {
    throw std::runtime_error(
      "The checklist " + checklist_path.string()
        + " does not mark the bye player: " + content);
  }
}
