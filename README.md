# Basic API for tracking CI state

## Versioning
  - Ruby 2.4.0 and above
  - Rails 5.1 and above
  - Postgre 0.18 and above

## Usage Example
* clone repo:
```
    cd projects
    git clone https://github.com/DmitryAvramec/traffic-light.git
  ```  
* Setup project for working with database:
```
cd projects/traffic-light
atom .
#This will open folder for atom, if u work with other editor open cloned folder with it
```
Rename config/database.yml.example to config/database.yml and set your credentials for postgre user

* Install gem dependencies `bundle install`
* Setup database:
```
rails db:create
rails db:migrate
#if this steps don't work, most likely you don't have permissions for it. Configure your PGuser first
 ```
 * Run server:	`rails s`

## Making API calls
This app is only for telling ESP module about CI state (if you want to integrate it, first implement processing from your CI). So here 2 steps to make it works:
### Esp module
* Open your sketch (example are in repo) with Arduino IDE (or other IDE for working with esp modules)
* Set SSID and SSID_PASS (Wifi name and password)
* Set url to your runnig server,  
	example: `http://192.168.100.47:3000/light/1`
    where `192.168.100.47` server handling devise IP, `:3000` port on it and `1` is id of your module for this server. If you have more then 1 - be carreful with this.
* Upload code to esp module (link for help http://arduino-project.net/nodemcu-v3-arduino-ide/, p.s. if you work with Linux, make sure that your user added to dialout group, for making usb visiable to Arduino IDE).
* Connect `D5`, `D6`, `D7` to `Red`,`Yellow`,`Green` leds.
### CI response
* For now you can just emulate response from CI:
```
POST
/notifications
http://192.168.100.47:3000/notifications
body: {
	"id": 1, # CI id. Set it for your module by adding ci_id on message, or add it manualy with console
    "result": 0 # 0 is ok 1 is fail
}
```
So, when we take `"result": 1` - `Red` led is lights, `Yellow` will lights when we get `"result": 0` from CI after `"result": 1`, and `Green` will lights when all is OK from start or after `Yellow`, when again get `"result": 0` from CI.
Enjoy!
