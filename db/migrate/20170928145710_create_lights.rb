class CreateLights < ActiveRecord::Migration[5.1]
  def change
    create_table :lights do |t|
      t.string :state, default: "red"
      t.string :last_remote_state
      t.string :ci_id, null: false

      t.timestamps
    end
  end
end
