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

                            <v-btn @click="submit()" color="primary">Register</v-btn>                    
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
              // eslint-disable-next-line
              this.alertMessage.value = error.response.data.error;
              this.alertVisible.value = true;
            });
        },
    }
}

</script>