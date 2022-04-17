<template>
  <div class="random">
    <b-container>
        <h1>Register</h1>

        <b-alert v-model="alertVisible" variant="danger" dismissible>
          {{alertMessage}}
        </b-alert>
        <b-row class="justify-content-md-center mt-3">
            <b-col col lg="4">
                <b-card class="mx-auto" style="max-width:350px;">
                    <b-form @submit="onSubmit" @reset="onReset">

                    <b-form-group id="username-label" label="Username:" label-for="username">
                        <b-form-input class="mx-auto" style="max-width:200px" id="username" v-model="form.username" placeholder="Enter username" required></b-form-input>
                    </b-form-group>

                    <b-form-group id="password-label" label="Password:" label-for="password">
                        <b-form-input class="mx-auto" style="max-width:200px" id="password" type="password" v-model="form.password" placeholder="Enter password" required></b-form-input>
                    </b-form-group>

                    <b-button @click="submit()" variant="primary">Register</b-button>                    </b-form>
                </b-card>
            </b-col>
        </b-row>
    </b-container>
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