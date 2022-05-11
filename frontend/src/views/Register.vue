<template>
  <div class="random">
    <v-container>
        <h1 style="font-family: 'Roboto', sans-serif;">Register</h1>

        <v-row class="justify-content-md-center mt-3">
            <v-col col lg="4">
                <v-card class="mx-auto" style="max-width:350px;">
                    <v-alert v-model="alertVisible" dense type="error" style="font-family: 'Roboto', sans-serif;">
                    {{alertMessage}}
                    </v-alert>
                    <v-container>
                        <v-form v-on:submit.prevent="">
                            <v-text-field class="mx-auto" style="max-width:200px" id="username" v-model="this.form.username" :counter="25" label="Nom d'utilisateur" required></v-text-field>

                            <v-text-field class="mx-auto" style="max-width:200px" id="password" type="password" v-model="this.form.password" :counter="25" label="Mot de passe" required></v-text-field>

                            <v-btn type="submit" @click="submit()" color="primary" style="font-family: 'Roboto', sans-serif;">Register</v-btn>                    
                        </v-form>
                    </v-container>
                </v-card>
            </v-col>
        </v-row>
    </v-container>
  </div>
</template>

<script>
import axios from 'axios';
import { ref } from 'vue';

export default {
    name: 'registerForm',
    data() {
        return {
            form: ref({
                username: '',
                password: '',
            }),
            alertMessage: '',
            alertVisible: false,
        }
    },
    methods: {
        submit: function() {
          const path = `${process.env.VUE_APP_BACKEND_URL}/register`;
          axios.post(path, this.form)
            .then((res) => {
              this.msg = res.data;
              window.location = "#/login"
            })
            .catch((error) => {
              this.alertMessage = error.response.data.error;
              this.alertVisible = true;
            });
        },
    }
}

</script>