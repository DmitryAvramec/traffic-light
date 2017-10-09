class LightController < ApplicationController
   protect_from_forgery with: :null_session

  def tell_state
    light = Light.find_or_create_by(id: params["id"])
    Light.update(light.id, ci_id: request["ci_id"]) if !light.ci_id && request["ci_id"]
    remote_state = request['current_state']
    if light.last_remote_state == light.state && remote_state != "off"
      action =  light.nothing
    else
      Light.update(light.id, last_remote_state: remote_state) unless light.last_remote_state == remote_state
      action = light.send(light.state)
    end
    render json: action.to_json
  end

  def process_ci_response
    light = Light.find_by(ci_id: request["id"])
    case request["result"]
    when 1
      state = "red"
    when 0
        state = light.state == "red" ? "yellow" : "green"
    end
    Light.update(light.id, state: state)
  end

end
