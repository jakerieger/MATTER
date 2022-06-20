#![cfg_attr(
  all(not(debug_assertions), target_os = "windows"),
  windows_subsystem = "windows"
)]

extern crate dirs;
use std::path::PathBuf;
use std::fs::File;
use std::io::BufReader;
use std::path::Path;
use std::error::Error;

fn main() {
  let context = tauri::generate_context!();
  tauri::Builder::default()
    .menu(tauri::Menu::os_default(&context.package_info().name))
    .invoke_handler(tauri::generate_handler![get_projects])
    .invoke_handler(tauri::generate_handler![create_project])
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

#[derive(serde::Deserialize, Debug)]
struct Projects {
  projects: Vec<Project>,
}

fn read_projects_from_file<P: AsRef<Path>>(path: P) -> Result<Projects, Box<dyn Error>> {
  let file = File::open(path)?;
  let reader = BufReader::new(file);
  let u = serde_json::from_reader(reader)?;

  Ok(u)
}

#[tauri::command]
fn get_projects() -> Vec<Project> {
  let mut projects_json =  PathBuf::new();
  projects_json.push(dirs::config_dir().unwrap());
  projects_json.push("MatterHub");
  projects_json.push("projects.json");
  println!("{:?}", projects_json);
  let projects = read_projects_from_file(projects_json).unwrap();

  return projects.projects;
}

#[tauri::command]
fn create_project(name: String, path: String) {
  // Create project folder
  println!("{:?}", name);
  println!("{:?}", path);
}