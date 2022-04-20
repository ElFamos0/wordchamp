<template>
  <div class="hello">
    <b-container>
        <b-form-group>
            <b-alert v-model="errorMessage" variant="danger" dismissible>
                {{errorMessage}}
            </b-alert>

            <div class="large-12 medium-12 small-12 cell">
                <label>Avatar : 
                    <input type="file" id="file" ref="file" v-on:change="gereEnvoi()"/>
                </label>
                <b-button variant="primary" v-if="file" v-on:click="envoiAvatar()">Envoyer</b-button>
            </div>

            <div class="large-12 medium-12 small-12 cell mt-4">
                <b-row class="my-1">
                    <b-col sm="2">
                        <label for="input-small">Username:</label>
                    </b-col>
                    <b-col sm="8">
                        <b-form-input id="input-small" size="sm" v-model="new_username" v-bind:placeholder="username"></b-form-input>
                    </b-col>
                    <b-col sm="2">
                        <b-button variant="primary" v-if="new_username" v-on:click="envoiUsername()">Envoyer</b-button>
                    </b-col>
                </b-row>
            </div>
        </b-form-group>
    </b-container>
  </div>
</template>

<script>
import { mapGetters } from 'vuex';
import axiosAuth from '@/api/axios-auth'
export default {
  name: 'profile-main',
  data(){
      return {
        file: null,
        new_username: null,
        errorMessage: null,
      }
  },
  computed: {
    ...mapGetters('auth', {
      username: 'getUsername'
    })
  },
  methods: {
      envoiUsername(){
        axiosAuth.post( '/profile_set/username', {"username":this.new_username}).then(response => {
            this.$store.dispatch('auth/changeUsername', response.data.new_username)
        }).catch((err) => {
                this.errorMessage = err.response.data.error;
        }).finally(() => {
            this.$router.push('/profile');
        });
      },
      envoiAvatar(){
            let formData = new FormData();
            formData.append('file', this.file);
            axiosAuth.post( '/profile_set/avatar',
                formData,
                {
                headers: {
                    'Content-Type': 'multipart/form-data'
                }
              }
            ).catch((err) => {
                this.errorMessage = err.response.data.error;
            }).finally(function(){
          this.$router.push('/profile');
        })
      },
      gereEnvoi(){
        this.file = this.$refs.file.files[0];
      }
    }
};
</script>