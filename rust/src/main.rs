mod handlers;
mod configs;
mod traits;
mod errors;

use core::error;
use std::io;

use handlers::{cli_handler::CliHandler, file_handler::FileHandler};

fn main() -> Result<(), Box<dyn error::Error>> {
  let cli_handler = CliHandler::new();

  let (input_file_path, search_string) = cli_handler.get_arguments()?;

  let mut file_handler = FileHandler::new(input_file_path.into());

  file_handler.search_files();

  Ok(())
}
