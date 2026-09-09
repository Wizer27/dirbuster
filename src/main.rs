use std::io::{BufReader,BufRead};
use std::fs::File;


async fn send_request(url:&str) -> Result<reqwest::Response, reqwest::Error>{
    let response = reqwest::get(url)
        .await?;
    Ok(response)
}



#[tokio::main]
async fn main(){
    let url = "https://google.com/";
    let file = File::open("dirs.txt").expect("Cannot open file");
    let reader = BufReader::new(file);
    for line in reader.lines() {
        let line = line.expect("Cannot read line");
        let new_url = format!("{}{}", url, line);
        let response = send_request(&new_url).await.unwrap();
        let status = response.status();
        let status_code:u16 = status.as_u16();
        if status_code != 404 && status_code != 403{
            println!("[+] URL: {}",new_url);
            println!("[+] STATUS CODE: {}",status_code);
        }

    }
}
