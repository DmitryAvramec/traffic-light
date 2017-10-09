class AddLastCiStateToLight < ActiveRecord::Migration[5.1]
  def change
    add_column :lights, :last_ci_state, :string
  end
end
