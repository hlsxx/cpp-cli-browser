mod handlers;
mod configs;
mod traits;

use handlers::cli_handler::CliHandler;

fn main() {
  let cli_handler = CliHandler::new();

  cli_handler.get_arguments();
}
