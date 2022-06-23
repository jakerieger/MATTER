#![cfg_attr(
  all(not(debug_assertions), target_os = "windows"),
  windows_subsystem = "windows"
)]

/** Copyright 2022 Jake Rieger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @note: I don't write Rust nor do I particularly like the language at all.
 * This code is probably "bad" in more ways than one, but Tauri is far better
 * than Electron overall so I'm content with dealing with Rust for this part of
 * the project.
 * 
 */

extern crate dirs;
use std::path::PathBuf;
use std::fs::File;
use std::io::BufReader;
use std::path::Path;
use std::error::Error;
extern crate tini;
use tini::Ini;

fn main() {
  let context = tauri::generate_context!();
  tauri::Builder::default()
    .menu(tauri::Menu::os_default(&context.package_info().name))
    .invoke_handler(tauri::generate_handler![get_projects, create_project, delete_project])
    .run(context)
    .expect("error while running tauri application");
}

#[derive(serde::Serialize, serde::Deserialize, Debug)]
struct Project {
  name: String,
  path: String,
  last_modified: u32,
  engine_version: String,
  favorite: bool,
}

#[derive(serde::Serialize, serde::Deserialize, Debug)]
struct SceneItem {
  id: u64,
  name: String,
}

#[derive(serde::Serialize, serde::Deserialize, Debug)]
struct BuildSettings {
  scenes: Vec<SceneItem>
}

#[derive(serde::Serialize, serde::Deserialize, Debug)]
struct ProjectConfig {
  name: String,
  engine_association: String,
  file_version: u64,
  description: String,
}

#[derive(serde::Serialize, serde::Deserialize, Debug)]
struct Projects {
  projects: Vec<Project>,
}

fn read_projects_from_file<P: AsRef<Path>>(path: P) -> Result<Projects, Box<dyn Error>> {
  let file = File::open(path)?;
  let reader = BufReader::new(file);
  let result = serde_json::from_reader(reader)?;

  Ok(result)
}

fn read_project_file<P: AsRef<Path>>(path: P) -> Result<ProjectConfig, Box<dyn Error>> {
  let file = File::open(path)?;
  let reader = BufReader::new(file);
  let result = serde_json::from_reader(reader)?;

  Ok(result)
}

#[tauri::command]
fn get_projects() -> Vec<Project> {
  let mut projects_json = PathBuf::new();
  projects_json.push(dirs::config_dir().unwrap());
  projects_json.push("MatterHub");
  projects_json.push("projects.json");
  let projects = read_projects_from_file(projects_json).unwrap();

  return projects.projects;
}

#[tauri::command]
fn create_project(name: String, path: String) {
  /**
   * We need to execute the following steps:
   * 
   * 1. Create the project directory at desired path
   * 2. Create directories for project structure
   * 3. Create the .matter project file
   * 4. Create the config files
   * 5. Create the C++ project files
   * 6. Add the project to our list of projects
   */

  let mut project_path = PathBuf::from(&path);
  project_path.push(&name);

  /** Step 1 */ 
  std::fs::create_dir(&project_path).expect("Error creating project directory!");

  /** Step 2 */ 
  let mut assets_dir = project_path.clone();
  assets_dir.push("Assets");
  let mut build_dir = project_path.clone();
  build_dir.push("Build");
  let mut config_dir = project_path.clone();
  config_dir.push("Config");
  let mut scenes_dir = project_path.clone();
  scenes_dir.push("Scenes");
  let mut source_dir = project_path.clone();
  source_dir.push("Source");

  std::fs::create_dir(&assets_dir).expect("Error creating Assets directory!");
  std::fs::create_dir(&build_dir).expect("Error creating Build directory!");
  std::fs::create_dir(&config_dir).expect("Error creating Config directory!");
  std::fs::create_dir(&scenes_dir).expect("Error creating Scenes directory!");
  std::fs::create_dir(&source_dir).expect("Error creating Source directory!");

  /** Step 3 */ 
  let project_config = ProjectConfig {
    name: name.clone(),
    engine_association: String::from("2022.6.15a"),
    file_version: 0,
    description: String::from("A new Matter project")
  };

  let mut project_config_path = project_path.clone();
  let project_name = format!("{}.matter", &name);
  project_config_path.push(&project_name);
  let project_config_out = serde_json::ser::to_string_pretty(&project_config).unwrap();
  std::fs::write(&project_config_path, project_config_out).expect("Error writing project file!");

  /** Step 4 */ 
  let mut default_game_path = config_dir.clone();
  default_game_path.push("DefaultGame.ini");
  let mut default_input_path = config_dir.clone();
  default_input_path.push("DefaultInput.ini");

  let default_game = Ini::new()
                      .section("ProjectSettings")
                      .item("ProjectID", "")
                      .item("ProjectName", name.clone())
                      .item("CompanyName", "")
                      .item("Homepage", "")
                      .item("DisplayName", "")
                      .section("BuildSettings")
                      .item("AppIcon", "")
                      .item("SplashImage", "")
                      .item("Version", "0.1.0");

  default_game.to_file(&default_game_path).unwrap();

  let default_input = Ini::new()
                        .section("AxisConfig")
                        .section("ActionConfig");

  default_input.to_file(&default_input_path).unwrap();

  /** Step 5 */ 
  let cmake_lists_content = r#"cmake_minimum_required(VERSION 3.23)

project(__PROJECT-NAME__)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

file(GLOB ALL_SRC
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/*.c"
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(__PROJECT-NAME__ ${ALL_SRC})
  "#.replacen("__PROJECT-NAME__", &name, 2);

  let mut cmake_lists_path = source_dir.clone();
  cmake_lists_path.push("CMakeLists.txt");
  let mut src_dir = source_dir.clone();
  src_dir.push("src");
  let mut include_dir = source_dir.clone();
  include_dir.push("include");

  std::fs::create_dir(&src_dir).expect("Error creating src directory");
  std::fs::create_dir(&include_dir).expect("Error creating include directory");
  std::fs::write(&cmake_lists_path, cmake_lists_content).expect("Error writing CMakeLists.txt to disk");

  /** Step 6 */
  let timestamp = std::time::SystemTime::now()
                  .duration_since(std::time::UNIX_EPOCH)
                  .expect("Error getting timestamp?")
                  .as_secs() as u32;

  let project = Project {
    name: name.clone(),
    path: format!("{}\\{}", &path, &name),
    last_modified: timestamp,
    engine_version: String::from("2022.6.15a"),
    favorite: false,
  };

  let mut projects_json = PathBuf::new();
  projects_json.push(dirs::config_dir().unwrap());
  projects_json.push("MatterHub");
  projects_json.push("projects.json");
  let mut projects = read_projects_from_file(&projects_json).unwrap();

  projects.projects.push(project);

  let projects_json_out = serde_json::ser::to_string_pretty(&projects).unwrap();
  std::fs::write(&projects_json, projects_json_out).expect("Error writing changes to projects.json");
}

#[tauri::command]
fn delete_project(id: u64) {
  let mut projects_json = PathBuf::new();
  projects_json.push(dirs::config_dir().unwrap());
  projects_json.push("MatterHub");
  projects_json.push("projects.json");
  let mut projects = read_projects_from_file(&projects_json).unwrap();

  // Store a copy of the project path
  let project_path = projects.projects[id as usize].path.clone();
  // Delete project from projects.json
  projects.projects.remove(id as usize);
  // Write changes to projects.json
  let projects_json_out = serde_json::ser::to_string_pretty(&projects).unwrap();
  std::fs::write(&projects_json, projects_json_out).expect("Error writing changes to projects.json!");

  // Delete the actual project directory
  std::fs::remove_dir_all(project_path).expect("Error deleting project directory!");
}