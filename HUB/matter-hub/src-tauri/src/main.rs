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

extern crate fs_extra;
use fs_extra::dir::{copy, CopyOptions};

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
  build_settings: BuildSettings,
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

  // Copy default project template to specified directory
  //
  // Why I can't just work with strings for paths, no idea...
  // Hence the dumb copying and creation of new PathBuf objects.
  // ¯\_(ツ)_/¯

  let project_path = PathBuf::from(&path);

  let mut project_template_path = PathBuf::new();
  project_template_path.push(dirs::config_dir().unwrap());
  project_template_path.push("MatterHub");
  project_template_path.push("templates");
  project_template_path.push("default_project");

  let options = CopyOptions::new();
  copy(project_template_path, project_path, &options).expect("Error copying project template");

  let mut proj_path_cp = PathBuf::from(&path);
  proj_path_cp.push("default_project");
  let mut new_proj_path = PathBuf::from(&path);
  new_proj_path.push(&name);

  std::fs::rename(&proj_path_cp, &new_proj_path).expect("Error renaming directory");
  
  let mut proj_file_path = new_proj_path.clone();
  let proj_name = format!("{}.matter", &name);
  proj_file_path.push(proj_name);
  new_proj_path.push("__PROJECT-NAME__.matter");
  std::fs::rename(&new_proj_path, &proj_file_path).expect("Error renaming project file");

  // Change contents of files where __PROJECT-NAME__ is referrenced to reflect the provided project name

  // Start with the project file itself (which is really just JSON)
  let mut project_config = read_project_file(&proj_file_path).unwrap();
  project_config.name = name.clone();

  let project_config_out = serde_json::ser::to_string_pretty(&project_config).unwrap();
  std::fs::write(&proj_file_path, project_config_out).expect("Error writing changes to project file");

  // Then do the CMakeLists.txt file in /Source
  let mut cmake_lists_path = PathBuf::from(&path);
  cmake_lists_path.push(&name);
  cmake_lists_path.push("Source");
  cmake_lists_path.push("CMakeLists.txt");
  
  let cmake_data = std::fs::read_to_string(&cmake_lists_path)
                                          .expect("Error reading CMakeLists.txt")
                                          .replacen("__PROJECT-NAME__", &name, 2);

  std::fs::write(&cmake_lists_path, cmake_data).expect("Error writing to CMakeLists.txt");

  // Finally, we can push the new project to the Projects array and update the UI
  let mut projects_json = PathBuf::new();
  projects_json.push(dirs::config_dir().unwrap());
  projects_json.push("MatterHub");
  projects_json.push("projects.json");
  let mut projects = read_projects_from_file(&projects_json).unwrap();
  
  let timestamp = std::time::SystemTime::now()
                    .duration_since(std::time::UNIX_EPOCH)
                    .expect("Error getting timestamp?")
                    .as_secs() as u32;

  let new_project = Project {
    name: name.clone(),
    path: format!("{}\\{}", &path, &name),
    last_modified: timestamp,
    engine_version: String::from("2022.6.15a"),
    favorite: false,
  };

  projects.projects.push(new_project);

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