<template>
  <div class="random">
    <v-container>
        <h1>Login</h1>
        <v-row class="justify-content-md-center mt-3">
            <v-col col lg="4">
                <v-card class="mx-auto" style="max-width:350px;">
                    <v-alert v-model="alertVisible" dense type="error">
                    {{alertMessage}}
                    </v-alert>
                    <v-container>
                        <v-form v-on:submit.prevent="onSubmit" @reset="onReset">
                            <v-text-field class="mx-auto" style="max-width:200px" id="username" v-model="this.form.username" :rules="nameRules" :counter="25" label="Username" required></v-text-field>

                            <v-text-field class="mx-auto" style="max-width:200px" id="password" type="password" v-model="this.form.password" :rules="nameRules" :counter="25" label="Password" required></v-text-field>

                            <v-btn type="submit" @click="submit()" color="primary">Login</v-btn>                    
                        </v-form>
                    </v-container>
                </v-card>
            </v-col>
        </v-row>
    </v-container>
  </div>
</template>

<script>
export default {
    name: 'loginForm',
    data() {
        return {
            form:{
                username: '',
                password: '',
            },
            alertMessage: '',
            alertVisible: false,
        }
    },
    methods: {
        submit: function() {
            this.$store.dispatch('auth/login', this.form)
            .then(() => {
                this.$router.push('/');
            })
            .catch(() => {
                this.$router.push('/login');
                this.alertVisible = true
                this.alertMessage = "Identifiants incorrects"
            })
        },
    }
}
</script>