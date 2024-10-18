mod handlers;
mod configs;
mod traits;
mod errors;

use core::error;
use std::io;

use handlers::cli_handler::CliHandler;

fn main() -> Result<(), Box<dyn error::Error>> {
  let cli_handler = CliHandler::new();

  let (input_file_path, search_string) = cli_handler.get_arguments()?;

  Ok(())
}
