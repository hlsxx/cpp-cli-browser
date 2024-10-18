use core::error;
use std::env;

use crate::{configs::cli_handler_config::{CliHandlerConfig, CliHandlerConfigBuilder}, traits::builder::Builder};

use crate::errors::argument_error::ArgumentError;

pub struct CliHandler {
  config: CliHandlerConfig
}

impl CliHandler {

  pub fn new() -> Self {
    Self {
      config: CliHandlerConfigBuilder::new().build()
    }
  }

  pub fn get_arguments(&self) -> Result<(String, String), Box<dyn error::Error>> {
    let args = env::args().collect::<Vec<String>>();

    if args.len() != 3 {
      return Err(Box::new(ArgumentError(
        "Not enough number of aguments, required 2(file path, search string)".to_string()
      )));
    }

    Ok((args[0].clone(), args[1].clone()))
  }

}
