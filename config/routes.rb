Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  post '/light/:id', to: 'light#tell_state'
  post '/notifications', to: 'light#process_ci_response'
end
