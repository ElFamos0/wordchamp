<template>
  <div class="random">
    <v-container>
        <h1>Register</h1>

        <v-alert v-model="alertVisible" type="danger" dismissible>
          {{alertMessage}}
        </v-alert>
        <v-row class="justify-content-md-center mt-3">
            <v-col col lg="4">
                <v-card class="mx-auto" style="max-width:350px;">
                    <v-container>
                        <v-form @submit="onSubmit" @reset="onReset">
                            <v-text-field class="mx-auto" style="max-width:200px" id="username" v-model="this.form.username" :rules="nameRules" :counter="25" label="Username" required></v-text-field>

                            <v-text-field class="mx-auto" style="max-width:200px" id="password" type="password" v-model="this.form.password" :rules="nameRules" :counter="25" label="Password" required></v-text-field>

                            <v-btn @click="submit()" color="primary">Login</v-btn>                    
                        </v-form>
                    </v-container>
                </v-card>
            </v-col>
        </v-row>
    </v-container>
  </div>
</template>

<script setup>
import {ref} from 'vue';
import axios from 'axios';


const form = ref({
    username: '',
    password: '',
})

const alertMessage = ref('')

const alertVisible = ref(false)

function submit() {
    const path = `${process.env.VUE_APP_BACKEND_URL}/register`;
      axios.post(path, form.value)
        .then((res) => {
          this.msg = res.data;
          window.location = "#/login"
        })
        .catch((error) => {
          // eslint-disable-next-line
          alertMessage.value = error.response.data.error;
          alertVisible.value = true;
        });
}

</script>